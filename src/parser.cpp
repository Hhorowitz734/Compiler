#include "parser.h"
#include "token.h"
#include <string>
#include <iostream>
#include <iomanip>


//Default constructor
Parser::Parser(const std::string& code) noexcept 
    : source_code(code),
    lexer(source_code.c_str()),
      curr_token(lexer.next()) {} //Sets the current token

//Moves curr_token pointer to the next token
void Parser::advance() noexcept {
    curr_token = lexer.next();
}

void Parser::process_token(const Token& token) noexcept {
    std::cout << std::setw(12) << token.get_type() << " |" << token.get_lexeme() << "|\n";
    // Here, you'll have logic to handle each type of token and build your AST or perform other parsing tasks.
}

void Parser::parse() noexcept {

    while(!curr_token.is_one_of(Token::Type::End, Token::Type::Unexpected)){ //Iterates until the end or until an unexpected character

        process_token(curr_token);
        advance();

    }

}
