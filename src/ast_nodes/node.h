#pragma once
#include "../token.h"


class Node {
    public:
        virtual ~Node() = default; //Virtual destructor
        //"Destructor will be called for any object that is derived from the class, even if the object is deleted through a pointer to the base class"

        enum class Node_Type { //Represents the type of the node, meant to simplify type comparison operations, similar token
            BinaryOperator,
            Literal,
            Comparison
        };

        //Comparison operations for node type
        bool is(Node_Type type) const noexcept;
        bool is_not(Node_Type type) const noexcept;
        bool is_one_of(Node_Type type1, Node_Type type2) const noexcept;
        template <typename... Ts>
        bool is_one_of(Node_Type type1, Node_Type type2, Ts... ks) const noexcept;

    
    private:
        Node_Type ntype; //Type of a given node
    
    protected:
        explicit Node(Node_Type type) : ntype(type) {}; //Constructor to set Node type
};

