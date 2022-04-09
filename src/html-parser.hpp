#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP

#include <string>
#include <vector>

class HTMLParser {
	public:
		HTMLParser();
		~HTMLParser();
		void parse(std::string filename);
		bool isBalanced(std::string filename);
		int pageVisitAmount(std::string filename);
	private:
		void pageVisitAmount_rec(std::string filename,
			std::vector<std::string> &_parsed,
			std::vector<std::string> &_visited,
			bool initial_call);
		std::vector<std::vector<std::string>> parsed; // outer = files, inner = tags in each page; 1st entry in each sub-arr = filename
		std::vector<std::vector<std::string>> visited; // outer = files, inner = pages that have been visited from that file; 1st entry in each sub-arr = filename
};

#endif
