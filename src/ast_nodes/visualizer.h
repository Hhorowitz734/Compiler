#include "node.h"
#include "operator_nodes.h"

class Visualizer {

    private:
        Node* root;

        std::string child_prefix = "├── ";
    
    public:
        
        void traverse(Node* node, int indent = 0) noexcept;
        

};
