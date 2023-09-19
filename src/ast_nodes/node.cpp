#include "node.h"


//Comparison methods
bool Node::is(Node_Type type) const noexcept { return ntype == type; }
bool Node::is_not(Node_Type type) const noexcept {return ntype != type; }
bool Node::is_one_of(Node_Type type1, Node_Type type2) const noexcept { return is(type1) || is(type2); }

template <typename... Ts>
bool Node::is_one_of(Node_Type type1, Node_Type type2, Ts... ks) const noexcept {
    return is(type1) || is_one_of(type2, ks...);
}

//Getters and setters
Node::Node_Type Node::get_type() const noexcept { return ntype; }
Node::possible_value_types Node::get_display_value() const noexcept { return display_value; }

void Node::set_display_value(const possible_value_types& new_value) noexcept { display_value = new_value; }


bool Node::has_children() const noexcept {
    //Returns whether a node has children or not based on its type
    switch(ntype){
        case Node_Type::BinaryOperator:
        case Node_Type::Comparison:
            return true;
        case Node_Type::Literal:
            return false;
        default:
            return false; //Should never reach this
    }
}

//Dummy functions
const Node* Node::get_left() const { return left; }
const Node* Node::get_right() const { return right; }