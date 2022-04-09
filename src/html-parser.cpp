#include "html-parser.hpp"
#include <iostream>
#include <fstream>
#include <stack>

HTMLParser::HTMLParser() {
	
}

HTMLParser::~HTMLParser() {
	
}

void HTMLParser::parse(std::string filename) {
	
	for (std::vector<std::string> arr : parsed){ // don't parse the same thing twice...
		if (arr[0] == filename){
			return;
		}
	}
	
	// new vector w/ filename at front
	
	std::vector<std::string> new_vector;
	new_vector.push_back(filename);
	
	// file_contents will hold entire file
	// https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream file(filename);
	if (!file.is_open()){
		return; // because file does not exist
	}
	std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	
	// loop thru; iteration is based on finding < and >; add each tag as an entry to new_vector
	
	// new_vector holds each tag excluding <>. e.g.
	// html, body, b, /b, a href=pages/woah.html, /a, /body, /html
	
	for (int i = file_contents.find("<"); i != -1; i = file_contents.find("<", i + 1)){
		std::string new_item = file_contents.substr(i + 1, file_contents.find(">", i) - i - 1);
		new_vector.push_back(new_item);
	}
	
	// publish results
	
	std::cout << "TAGS:\n";
	if (new_vector.size() == 1){
		std::cout << "- there is nothing.\n";
	}
	for (std::string str : new_vector){
		if (str != new_vector[0]){
			std::cout << "- " << str << "\n";
		}
	}
	
	parsed.push_back(new_vector);
}

bool HTMLParser::isBalanced(std::string filename) {
	
	for (std::vector<std::string> arr : parsed){ // find filename's parse vector
		if (arr.front() == filename){
			std::stack<std::string> stack;
	
			for (std::string str : arr){ // loop thru all tags in parse vector
				if (str != arr.front()){ // ignore parse vector's 1st entry, which is the page's filename
					if (str.at(0) == '/'){
						if (stack.empty() || stack.top().substr(0, stack.top().find(" ")) != str){
							return false; // because it found a </> with no matching < >
						}
						stack.pop();
					}
					else{
						stack.push("/" + str); // pushes it with the / added, so that the above match check is streamlined
					}
				}
			}
			
			if (!stack.empty()){
				return false; // because there was a < > with no matching </>
			}
			
			return true;
		}
	}
	
	return false;
}

void HTMLParser::pageVisitAmount_rec(std::string filename,
	std::vector<std::string> &_parsed,
	std::vector<std::string> &_visited,
	bool initial_call) {
	
	bool found_match = false;
	
	// check for if the examined file already exists in _visited
	
	for (std::string str : _visited){
		if (str == filename){
			if (!initial_call){ // 0th entry is original filename... so ignore this on initial rec call
				return;
			}
			found_match = true;
		}
	}
	
	// don't allow imbalanced files
	
	if (!isBalanced(filename)){
		return;
	}
	
	// add to list of files visited from initial inquiry
	
	if (!found_match){
		_visited.push_back(filename);
	}
	
	// scan for links
	
	for (std::string str : _parsed){
		if (str.rfind("a href=", 0) == 0){ // "a href=" at start
			std::string new_file = str.substr(str.find("=") + 1); // everything after =
			parse(new_file);
			for (std::vector<std::string> arr : parsed){ // find the parse-vector's entry for new_file
				if (arr[0] == new_file){
					pageVisitAmount_rec(new_file, arr, _visited, false);
				}
			}
		}
	}
}

int HTMLParser::pageVisitAmount(std::string filename) {
	
	// check if pageVisitAmount(filename) has already been called
	
	for (std::vector<std::string> arr : visited){
		if (arr[0] == filename){
			return (arr.size() - 1);
		}
	}
	
	// make a new vector, w/ item 0 being the examined file's name
	
	std::vector<std::string> new_vector;
	new_vector.push_back(filename);
	
	// find the parse-vector's entry for filename
	
	for (std::vector<std::string> arr : parsed){
		if (arr[0] == filename){
			pageVisitAmount_rec(filename, arr, new_vector, true);
		}
	}
	
	// publish results
	
	visited.push_back(new_vector);
	return new_vector.size() - 1;
}
