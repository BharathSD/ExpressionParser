//
// Created by asus on 11/24/2018.
//

#ifndef UNTITLED_UTILITY_H
#define UNTITLED_UTILITY_H

#include <map>
#include <string>
class Tokens : public std::vector<std::string>
{
public:
    friend std::ostream &operator<<(std::ostream &os, const Tokens &tokens)
    {
        for(auto& token : tokens)
            os << token << "\t";
        return os;
    }

};

class ExpressionUtility
{
public:
    static bool isOperator( const std::string& token)
    {
        return token == "+" || token == "-" ||
               token == "*" || token == "/";
    }

    static bool isParenthesis( const std::string& token)
    {
        return token == "(" || token == ")";
    }
};

namespace
{
    enum ASSOC
    {
        LEFT = 0,
        RIGHT = 1
    };

    // define operation map associations

    typedef std::map<std::string, std::pair< int,int >> OpMap;

    const OpMap::value_type assocs[] =
            {  OpMap::value_type( "+", std::make_pair<int,int>( 0, ASSOC ::LEFT) ),
               OpMap::value_type( "-", std::make_pair<int,int>( 0, ASSOC ::LEFT ) ),
               OpMap::value_type( "*", std::make_pair<int,int>( 5, ASSOC ::LEFT ) ),
               OpMap::value_type( "/", std::make_pair<int,int>( 5, ASSOC ::LEFT ) ) };

    const OpMap opmap( assocs, assocs + sizeof( assocs ) / sizeof( assocs[ 0 ] ) );


    // support functions for expression parsing


// Test if token is an operator


// Test associativity of operator token
    bool isAssociative( const std::string& token, const int& type)
    {
        const std::pair<int,int> p = opmap.find( token )->second;
        return p.second == type;
    }

// Compare precedence of operators.
    int cmpPrecedence( const std::string& token1, const std::string& token2 )
    {
        const std::pair<int,int> p1 = opmap.find( token1 )->second;
        const std::pair<int,int> p2 = opmap.find( token2 )->second;

        return p1.first - p2.first;
    }


}
#endif //UNTITLED_UTILITY_H
