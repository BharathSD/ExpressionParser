//
// Created by asus on 11/24/2018.
//

#include "TokenGenerator.h"
using namespace std;
TokenGenerator::TokenGenerator(const std::string &expression) : m_expression(expression)
{
    parseExpression();
}

void TokenGenerator::parseExpression() {
    std::string str;

    for (int itr = 0; itr < static_cast<int>(m_expression.length()); ++itr) {
        const std::string token( 1, m_expression[ itr ] );

        if (ExpressionUtility::isOperator(token) || ExpressionUtility::isParenthesis(token))
        {
            if (!str.empty())
            {
                m_tokens.push_back(str);
            }
            str=""; // empty the string
            m_tokens.push_back(token);
        }
        else
        {
            // append the numbers
            if ( !token.empty() && token != " " ) // if token is not empty or not equal to space
            {
                str.append( token );
            }
            else
            {
                if ( !str.empty() )
                {
                    m_tokens.push_back( str );
                    str = "";
                }
            }
        }
    }
}

const Tokens &TokenGenerator::get_tokens() const {
    return m_tokens;
}

std::ostream &operator<<(std::ostream &os, const TokenGenerator &generator) {
    os << "m_tokens: " << generator.m_tokens;
    return os;
}
