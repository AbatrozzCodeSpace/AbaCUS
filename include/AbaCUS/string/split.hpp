#ifndef ABACUS_STRING_SPLIT_HPP
#define ABACUS_STRING_SPLIT_HPP

#include <string>
#include <sstream>
#include <vector>

namespace abacus {
	namespace string {
		inline void split(const std::string &s, char delim, std::vector<std::string> &elems) {
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				elems.push_back(item);
			}
		}
	}
}

#endif