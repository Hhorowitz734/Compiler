#include "parser.h"
#include "token.h"
#include <string>
#include <iostream>
#include <iomanip>


//Default constructor
Parser::Parser(const std::string& code) noexcept 
    : source_code(code),
    lexer(source_code.c_str()),
      curr_token(lexer.next()), //Sets the current token
      next_token(Token::Type::Unexpected) {} //Temporarily sets next token with unexpected type



//Looking forwards methods -------------

void Parser::advance() noexcept { //Advances to the next token without checking type
    if (has_peeked){
        curr_token = next_token;
        has_peeked = false;
    } else {
        curr_token = lexer.next();
    }
}

Token Parser::peek() noexcept { //Returns the next token without advancing to it
    if (!has_peeked){
        next_token = lexer.next();
        has_peeked = true;
    } 
    return next_token;
}

void Parser::consume(Token::Type expected_type) { //Compares token to expected type, then advances
    if (!curr_token.is(expected_type)){ //Throws error if type is unexpected
        throw std::runtime_error("Unexpected Token.");
    }
    advance();
}



//Expression handling methods

double Parser::expression() noexcept {
    //Processes an expression by checking if it 
    return 0.0;
}



//Testing methods -------------

void Parser::print_token(const Token& token) noexcept { 

    // TODO: Tries to match next token with expected token type
    // Throws an error if that doesn't work

    std::cout << std::setw(12) << token.get_type() << " |" << token.get_lexeme() << "|\n";
    // Here, you'll have logic to handle each type of token and build your AST or perform other parsing tasks.
}

double Parser::expression() noexcept {
    //Processes an expression by checking if it 
    return 0.0;
}



//Main parser method -------------

void Parser::parse() noexcept {

    while(!curr_token.is_one_of(Token::Type::End, Token::Type::Unexpected)){ //Iterates until the end or until an unexpected character

        print_token(curr_token);
        advance();

    }

}
