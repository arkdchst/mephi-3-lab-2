#pragma once

#include <memory>
#include <string>

#include "dict.hpp"

class WordIsTooLargeError : public std::runtime_error{
public:
	WordIsTooLargeError() : std::runtime_error("word is too large"){}
};


List<std::string> split(std::string text);

std::unique_ptr<IDictionary<std::string, int>> createIndexW(const std::string &text, int max_count);

std::unique_ptr<IDictionary<std::string, int>> createIndexS(const std::string &text, int max_count);

std::unique_ptr<IDictionary<int, List<std::string>>> reduceIndex(IDictionary<std::string,int> *index);