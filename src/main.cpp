/*
Student Name: Chris Koenig
Program Name: HTML Parser
Creation Date: Spring 2021 (date unknown)
Last Modified Date: Spring 2021 (date unknown)
CSCI Course: CSCI 315
Grade Received: (unknown)
Design Comments: (n/a)
*/

#include <iostream>
#include <sstream>
#include "html-parser.hpp"

/* Used to trim whitespace around a string.
 */
std::string trim(std::string const& str) {
	std::string word;
	std::stringstream stream(str);
	stream >> word;

	return word;
}

int main(int argc, char *argv[]) {
	// Get the program name;
	std::string programName = trim(argv[0]);
	HTMLParser htmlParser;

	// First we parse each page
	for (int i = 1; i < argc; i++) {
		// get each argument to the program.
		std::string htmlpage = argv[i];

		// If the argument is not the program
		size_t pos = htmlpage.find(programName);
		if (pos == std::string::npos) {
			// then ask to parse the HTML page.
			std::cout << "Parsing: '" << htmlpage << "'\n";
			htmlParser.parse(htmlpage);
			std::cout << "\n"; // added
		}
	}

	// Second we print the results
	for (int i = 1; i < argc; i++) {
		// get each argument to the program.
		std::string htmlpage = argv[i];

		// If the argument is not the program
		size_t pos = htmlpage.find(programName);
		if (pos == std::string::npos) {
			/* then print out if it is balanced and number of web pages
			 * that can be visited from the page
			 */
			std::cout << htmlpage << " is " <<
				(htmlParser.isBalanced(htmlpage) ? "" : "not ") <<
				"balanced." << "\n";
			std::cout << htmlpage << " can visit " << 
				htmlParser.pageVisitAmount(htmlpage) << " pages.\n";
		}
		std::cout << "\n"; // added
	}
}
