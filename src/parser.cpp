#include "parser.h"
#include "token.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <charconv> 
//To implement efficient stringview to double


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

double Parser::expr() noexcept {
    
    double value = term();

    while (curr_token.is_one_of(Token::Type::Plus, Token::Type::Minus)){
        Token::Type op = curr_token.get_type();
        advance();

        double next_value = term();

        if (op == Token::Type::Plus){
            value += next_value;
        } else if (op == Token::Type::Minus){
            value -= next_value;
        }
    }
    
    return value;

}

double Parser::factor() {

    if (curr_token.is(Token::Type::Number)){ //If token is a number, returns that number
        double value = sv_to_double(curr_token.get_lexeme()); //stod takes a numeric value from a string
        advance();
        return value;
    } else if (curr_token.is(Token::Type::LeftParen)){
        advance();
        double value = expr(); //Recursive call for expression inside parentheses
        consume(Token::Type::RightParen);
        return value;
    } else {
        throw std::runtime_error("Unexpected token in factor."); //I aim to create better error statements in the future
    }


}

double Parser::term() noexcept {

    double value = factor();

    while(curr_token.is_one_of(Token::Type::Asterisk, Token::Type::Slash)){
        Token::Type op = curr_token.get_type();
        advance(); 
        double next_value = factor(); //Gets the second number for multiplying/dividing

        if (op == Token::Type::Asterisk){
            value *= next_value;
        } else if (op == Token::Type::Slash){
            value /= next_value;
        }
    }

    return value;

}


//Helper methods -------------

double Parser::sv_to_double(std::string_view sv){
    //Converts string view to double efficiently
    char buffer[64];  // assuming max number length is < 64; adjust as needed
    if(sv.size() >= sizeof(buffer)) {
        throw std::runtime_error("Number too long");
    }
    std::copy(sv.begin(), sv.end(), buffer);
    buffer[sv.size()] = '\0';
    return strtod(buffer, nullptr);
}



//Testing methods -------------

void Parser::print_token(const Token& token) noexcept { 
    std::cout << std::setw(12) << token.get_type() << " |" << token.get_lexeme() << "|\n";
}

void Parser::parse_arithmetic() noexcept { //Test case to parse arithmetic expressions

    //Can handle expressions such as "(5 * (3 / 2)) + 1" or "(3 + 3) * (5 - 1)"

    if (curr_token.is(Token::Type::Number) //Testing our arithmetic processing
        || curr_token.is(Token::Type::LeftParen) 
        || curr_token.is(Token::Type::Minus)) {
        double result = expr();
        std::cout << "Result: " << result << std::endl;
    }

}



//Main parser method -------------

void Parser::parse() noexcept {

    while(!curr_token.is_one_of(Token::Type::End, Token::Type::Unexpected)){ //Iterates until the end or until an unexpected character

        
        if (curr_token.is(Token::Type::Number) //Testing our arithmetic processing
           || curr_token.is(Token::Type::LeftParen) 
           || curr_token.is(Token::Type::Minus)) {
            double result = expr();
            std::cout << "Result: " << result << std::endl;
            break;
        }
        
    }

}
