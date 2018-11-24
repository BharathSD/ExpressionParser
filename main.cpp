#include <iostream>
#include "TokenGenerator.h"
#include "TokenParser.h"

using namespace std;
int main() {
    std::string s = "( 1 + 2) * ( 3 / 4 )-(5+6)";

    TokenGenerator tokenGenerator(s);

    Tokens tokens = tokenGenerator.get_tokens();

    TokenParser tokenParser(tokens);

	std::cout   << "Result of " << s << " : " 
				<< tokenParser.get_result() << std::endl;
	system("pause");
    return 0;
}