#include "visualizer.h"
#include "node.h"
#include "operator_nodes.h"
#include <iostream>
#include <string>

void Visualizer::display(Node* node, int indent = 0, std::string prefix = "") noexcept {
    
    if (!node) return;

    for (int i = 0; i < indent; i++){ 
        //Sets up the spaces for indent
        std::cout << continuation_prefix;
    }
    
    std::cout << prefix << "node!" << '\n';
    std::cout << node->get_right()->has_children() << '\n'; //This throws a segfault

    if (node->has_children()){
        display(node->left, indent + 1, child_prefix);

        if (node->left && node->right) {
            for (int i = 0; i < indent; ++i) {
                std::cout << continuation_prefix;
            }
            std::cout << "└── " << "Node!!" << std::endl;
            display(node->right, indent + 1, "    ");
        } else {
            display(node->right, indent + 1, child_prefix);
        }
    }


}