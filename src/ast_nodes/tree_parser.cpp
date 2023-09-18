#include "tree_parser.h"
#include "node.h"
#include "../token.h"
#include "../lexer.h"

#include <iostream> //TEST

//Looking forwards methods

void TreeParser::advance() noexcept {
    if (has_peeked){
        curr_token = next_token;
        has_peeked = false;
    } else {
        curr_token = lexer.next();
    }
}

Token TreeParser::peek() noexcept {
    if (!has_peeked){
        next_token = lexer.next();
        has_peeked = true;
    }
    return next_token;
}

void TreeParser::consume(Token::Type expected_type) {
    if (!curr_token.is(expected_type)){
        throw std::runtime_error("Unexpected Token.");
    }
    advance();
}


//Expression handling methods

std::unique_ptr<Node> TreeParser::plus_minus() {
    //Handles plus and minus operations 
    //Creates a BinaryOpNode with the operator and two literals

    std::cout << "plus_minus" << '\n'; //TEST

    std::unique_ptr<Node> left = mult_div();

    while(peek().is_one_of(Token::Type::Plus, Token::Type::Minus)){

        Token::Type opr_type = peek().get_type(); //Figures out the next operator, consumes it
        advance(); //consume(opr_type); TEST

        //Gets the right ptr of this node (will be a literal)
        std::unique_ptr<Node> right = mult_div();

        //Make unique creates a new instance and returns a std::unique_ptr to that instance
        left = std::make_unique<BinaryOpNode>(opr_type, std::move(left), std::move(right));
    }

    return left;

}

std::unique_ptr<Node> TreeParser::mult_div() {
    //Handles multiplication and division operations
    //Creates a BinaryOpNode with the operator and two literals

    std::cout << "mult_div" << '\n'; //TEST

    std::unique_ptr<Node> left = primary();

    while (peek().is_one_of(Token::Type::Asterisk, Token::Type::Slash)){
        
        Token::Type opr_type = peek().get_type();
        advance(); //consume(opr_type); TEST

        //Gets the right ptr of this node (literal)
        std::unique_ptr<Node> right = primary();

        left = std::make_unique<BinaryOpNode>(opr_type, std::move(left), std::move(right));
    }

    return left;

}

std::unique_ptr<Node> TreeParser::primary() {
    //Handles parentheses and literals

    std::cout << "primary" << '\n'; //TEST

    Token next_type = peek(); //We are checking out the next token
    
    switch(next_type.get_type()){ //Switch statement to check the type of the next token

        case Token::Type::Number:
            advance();
            return std::make_unique<LiteralNode>(sv_to_double(next_type.get_lexeme()));
        case Token::Type::LeftParen:
            consume(Token::Type::LeftParen);
            { //Defined a block scope to prevent issues with expr_result
            std::unique_ptr<BinaryOpNode> expr_result = std::unique_ptr<BinaryOpNode>(static_cast<BinaryOpNode*>(plus_minus().release()));
            advance();
            return expr_result;
            }
        default:
            throw std::runtime_error("Unexpected token in factor.");
    };


}


//Helper methods -------------

double TreeParser::sv_to_double(std::string_view sv){
    //Converts string view to double efficiently
    char buffer[64];  // assuming max number length is < 64; adjust as needed
    if(sv.size() >= sizeof(buffer)) {
        throw std::runtime_error("Number too long");
    }
    std::copy(sv.begin(), sv.end(), buffer);
    buffer[sv.size()] = '\0';
    return strtod(buffer, nullptr);
}



//Main method

std::unique_ptr<Node> TreeParser::parse(){

    std::unique_ptr<Node> result = plus_minus();
    if(result->is(Node::Node_Type::BinaryOperator)){
        std::cout << "Head node in binary operator\n";
    }
    return result;

}