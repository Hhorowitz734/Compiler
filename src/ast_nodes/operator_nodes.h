#include "../token.h"
#include "node.h"
#include <iostream> //TEST
#pragma once

class LiteralNode : public Node {

    private:
        //Sets up a value
        Node::possible_value_types val;

        

    public:
        //Constructors for each of the three allowed types
        LiteralNode(int num) 
            : Node(Node_Type::Literal), val(num) { set_display_value(val); }
        LiteralNode(double num) 
            : Node(Node_Type::Literal), val(num) { set_display_value(val); }
        LiteralNode(long num) 
            : Node(Node_Type::Literal), val(num) { set_display_value(val); }

        //Infers type as we don't know which one will be used
        const auto& get_value() const { return val; }

};

class BinaryOpNode : public Node {
    //Handles binary operations
    //Takes in two values (l and r)

    private:
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Token::Type opr; //Operator
    
    public:
        BinaryOpNode(Token::Type op, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
            : Node(Node_Type::BinaryOperator), opr(op), left(std::move(l)), right(std::move(r)) 
            { set_display_value("Opr [Fill later]");
            std::cout << l->get_display_value(); //TEST 
            /* ok so heres what im trying to do:
               1) print the l and r children in the constructor
                  so that this runs when a BinaryOpNode is created from TreeParser
               2) To do that, I need to fix the possible_value_types tihng in node to make it printable
                   Try to do that with a to_string custom function for the type if possible but if not then fuck
               3) Make sure the nodes are being linked togehter properly
            */
             } 



        const Token::Type get_operator() const { return opr; }  
        const Node* get_left() const override { return left.get(); }
        const Node* get_right() const override { return right.get(); }
        //unique_ptr's get() method allows you to get a raw pointer to thing its referencing
};

class ComparisonNode : public Node {
    //Handles comparisons (=, <, >)
    private:

        Token::Type opr;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

    public:

        ComparisonNode(Token::Type op, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : Node(Node_Type::Comparison), opr(op), left(std::move(l)), right(std::move(r)) 
        { set_display_value("Comparison (fix later)"); }

};