#pragma once
#include "../token.h"


class Node {
    public:

        //Possible value types that a node's display value can be
        using possible_value_types = std::variant<std::string, int, long, double>;

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

        bool has_children() const noexcept;

        //Getters and setters
        Node_Type get_type() const noexcept;
        possible_value_types get_display_value() const noexcept;
        void set_display_value(const possible_value_types& new_value) noexcept;

        //Dummy variables and methods, not used in nodes without children
        Node* left;
        Node* right;
        virtual const Node* get_left() const;
        virtual const Node* get_right() const;
    
    private:
        Node_Type ntype; //Type of a given node
        possible_value_types display_value; //What the node will be displayed as on the visualizer
    
    protected:
        explicit Node(Node_Type type) : ntype(type) {}; //Constructor to set Node type
};


//Function to print the possible_value_types type
std::ostream& operator<<(std::ostream& os, const Node::possible_value_types& value);
