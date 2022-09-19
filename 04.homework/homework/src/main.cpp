// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
//    std::cout << "-- Старт --" << std::endl;

    Lexer lexer(std::cin);

    Parser parser(lexer);

    ASTNode *ast = parser.parse();
    if (ast) {
         ast->print(std::cout);
    }
    std::cout << "-- Финиш --" << std::endl;
    return 0;
}
