//
// Created by asus on 11/24/2018.
//

#include "TokenParser.h"
#include <iostream>
TokenParser::TokenParser(const Tokens &m_tokens) : m_tokens(m_tokens)
{
    if(convert2ReversePolishNotation())
    {
		m_computedResult = compute_result();
    }
}

double TokenParser::get_result()
{
	return m_computedResult;
}

bool TokenParser::convert2ReversePolishNotation()
{
    bool success = true;
    std::list<std::string> out;
    std::stack<std::string> stack;

    // While there are tokens to be read
    for ( auto& token : m_tokens)
    {

        // If token is an operator
        if ( ExpressionUtility::isOperator( token ) )
        {
			/*
			 * If there is an operator token at the top of the stack say o2
				* And if the current operator token (say o1) is left associative
				* And its precedence is equal to that of o2 or has less precedence 
			 */
            const std::string o1 = token;

            if ( !stack.empty() )
            {
                std::string o2 = stack.top();

                while ( ExpressionUtility::isOperator( o2 ) &&
                        ( ( isAssociative( o1, ASSOC::LEFT ) &&  cmpPrecedence( o1, o2 ) == 0 ) ||
                          ( cmpPrecedence( o1, o2 ) < 0 ) ) )
                {
                    // pop o2 off the stack, onto the output queue;
                    stack.pop();
                    out.push_back( o2 );

                    if ( !stack.empty() )
                        o2 = stack.top();
                    else
                        break;
                }
            }

            // push o1 onto the stack.
            stack.push( o1 );
        }
            // If the token is a left parenthesis, then push it onto the stack.
        else if ( token == "(" )
        {
            // Push token to top of the stack
            stack.push( token );
        }
            // If token is a right bracket ')'
        else if ( token == ")" )
        {
            // Until the token at the top of the stack is a left parenthesis,
            // pop operators off the stack onto the output queue.
            std::string topToken  = stack.top();

            while ( topToken != "(" )
            {
                out.push_back(topToken );
                stack.pop();

                if ( stack.empty() ) break;
                topToken = stack.top();
            }

            // Pop the left parenthesis from the stack, but not onto the output queue.
            if ( !stack.empty() ) stack.pop();

            // If the stack runs out without finding a left parenthesis,
            // then there are mismatched parentheses.
            if ( topToken != "(" )
            {
                return false;
            }
        }
            // If the token is a number, then add it to the output queue.
        else
        {
            out.push_back( token );
        }
    }

    // While there are still operator tokens in the stack:
    while ( !stack.empty() )
    {
        const std::string stackToken = stack.top();

        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if ( ExpressionUtility::isParenthesis( stackToken )   )
        {
            return false;
        }

        // Pop the operator onto the output queue./
        out.push_back( stackToken );
        stack.pop();
    }

    strArray.assign( out.begin(), out.end() );
    return success;
}

double TokenParser::compute_result()
{
	std::stack<std::string> st;
	// For each token        
	for (auto& token : strArray)
	{
		// If the token is a value push it onto the stack        
		if (!ExpressionUtility::isOperator(token))
		{
			st.push(token);
		}
		else
		{
			double result = 0.0;

			// Token is an operator: pop top two entries        
			const std::string val2 = st.top();
			st.pop();
			const double d2 = strtod(val2.c_str(), NULL);

			if (!st.empty())
			{
				const std::string val1 = st.top();
				st.pop();
				const double d1 = strtod(val1.c_str(), NULL);

				//Get the result        
				result = token == "+" ? d1 + d2 :
					token == "-" ? d1 - d2 :
					token == "*" ? d1 * d2 :
					d1 / d2;
			}
			else
			{
				if (token == "-")
					result = d2 * -1;
				else
					result = d2;
			}


			// Push result onto stack       
			std::ostringstream s;
			s << result;
			st.push(s.str());
		}
	}

	return strtod(st.top().c_str(), NULL);
}

