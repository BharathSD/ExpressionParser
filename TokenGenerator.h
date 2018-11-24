//
// Created by asus on 11/24/2018.
//

#ifndef EXPRESSIONPARSER_TOKENGENERATOR_H
#define EXPRESSIONPARSER_TOKENGENERATOR_H

#include <vector>
#include <string>
#include <ostream>
#include "Utility.h"

class TokenGenerator {
    std::string m_expression;
    Tokens m_tokens;

    void parseExpression();

public:
    TokenGenerator(const std::string &expression);

    const Tokens &get_tokens() const;

    friend std::ostream &operator<<(std::ostream &os, const TokenGenerator &generator);
};


#endif //EXPRESSIONPARSER_TOKENGENERATOR_H
