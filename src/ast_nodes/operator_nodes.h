#include "../token.h"
#include "node.h"

class LiteralNode : public Node {

    private:
        std::variant<int, double, long> val;
        //std::variant allows for one of these 3 types to be chosen

    public:
        //Constructors for each of the three allowed types
        LiteralNode(int num) 
            : Node(Node_Type::Literal), val(num) {};
        LiteralNode(double num) 
            : Node(Node_Type::Literal), val(num) {};
        LiteralNode(long num) 
            : Node(Node_Type::Literal), val(num) {};

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
            : Node(Node_Type::BinaryOperator), opr(op), left(std::move(l)), right(std::move(r)) {};



        const Token::Type get_operator() const { return opr; }  
        const Node* get_left() const { return left.get(); }
        const Node* get_right() const { return right.get(); }
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
        : Node(Node_Type::Comparison), opr(op), left(std::move(l)), right(std::move(r)) {};

};