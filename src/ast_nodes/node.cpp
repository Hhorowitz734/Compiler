#include "node.h"

//Comparison methods
bool Node::is(Node_Type type) const noexcept { return ntype == type; }
bool Node::is_not(Node_Type type) const noexcept {return ntype != type; }
bool Node::is_one_of(Node_Type type1, Node_Type type2) const noexcept { return is(type1) || is(type2); }

template <typename... Ts>
bool Node::is_one_of(Node_Type type1, Node_Type type2, Ts... ks) const noexcept {
    return is(type1) || is_one_of(type2, ks...);
}