#ifndef lexer_hpp
#define lexer_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "token.hpp"

std::vector<Token*> Tokenise(std::string text);

std::string UnicodeToUTF8(unsigned int codepoint);

void EraseFront(std::string *text, int *current, int length);

#endif