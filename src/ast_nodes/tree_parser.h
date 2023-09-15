#include "../token.h"
#include "../lexer.h"
#include "operator_nodes.h"


class TreeParser {
    //Parser an AST Tree defined based on the given nodes
    private:
        Lexer lexer;
        Token curr_token;
        Token next_token;
        std::string source_code;
        
        Token peek() const;
        Token consume(Token::Type t);

        std::unique_ptr<Node> expression();
        std::unique_ptr<Node> plus_minus();
        std::unique_ptr<Node> mult_div();
        std::unique_ptr<Node> primary(); //Handles literals and parentheses

    public:
        //Default constructor -> Initializes vector with source code
        TreeParser(std::string code) 
            : source_code(code), 
            lexer(source_code.c_str()), 
            curr_token(lexer.next()),
            next_token(Token::Type::Unexpected) {}; //next_token should never be used as Token::Type::Unexpected


};