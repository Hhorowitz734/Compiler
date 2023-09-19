#pragma once
#include "../token.h"
#include "../lexer.h"
#include "operator_nodes.h"


class TreeParser {
    //Parser an AST Tree defined based on the given nodes
    private:
        //Properties
        std::string source_code;
        Lexer lexer;
        Token curr_token;
        Token next_token;
        bool has_peeked = false;
        
        //Move forward methods
        void advance() noexcept;
        Token peek() noexcept;
        void consume(Token::Type t);

        //Recursive descent parsing
        std::unique_ptr<Node> plus_minus();
        std::unique_ptr<Node> mult_div();
        std::unique_ptr<Node> primary(); //Handles literals and parentheses

        //Helper methods
        double sv_to_double(std::string_view sv);

    public:
        //Default constructor -> Initializes vector with source code
        TreeParser(std::string code) 
            : source_code(code), 
            lexer(source_code.c_str()), 
            curr_token(lexer.next()),
            next_token(Token::Type::Unexpected) {}; //next_token should never be used as Token::Type::Unexpected

        //Main method
        std::unique_ptr<Node> parse();

};