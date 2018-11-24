//
// Created by asus on 11/24/2018.
//

#ifndef EXPRESSIONPARSER_TOKENPARSER_H
#define EXPRESSIONPARSER_TOKENPARSER_H

#include <list>
#include <stack>
#include <vector>
#include "Utility.h"
#include <sstream>

class TokenParser {
    Tokens m_tokens;
    std::vector< std::string> strArray;
	double m_computedResult{ 0 };

    bool convert2ReversePolishNotation();

	double compute_result();

public:
    TokenParser(const Tokens &m_tokens);

	double get_result();
};


#endif //EXPRESSIONPARSER_TOKENPARSER_H
