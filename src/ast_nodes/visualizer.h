#pragma once
#include "node.h"
#include "operator_nodes.h"

class Visualizer {

    private:
        Node* root;

        std::string child_prefix = "├── ";
        std::string continuation_prefix = "│   ";
    
    public:
        Visualizer(Node* tree_root) : root(tree_root) {};

        //Displays the AST
        void display(Node* node, int indent,  std::string prefix) noexcept;

        

};
