#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "ast_nodes/tree_parser.h"
#include "ast_nodes/visualizer.h"


//g++ -std=c++17 main.cpp parser.cpp lexer.cpp token.cpp -o main
//g++ -std=c++17 main.cpp ast_nodes/tree_parser.cpp ast_nodes/node.cpp ast_nodes/visualizer.cpp lexer.cpp token.cpp -o main


int main() {
  auto code =
      "x = 2\n"
      "## This is a comment.\n"
      "var x\n"
      "var y\n"
      "var f = function(x, y) { sin(x) * sin(y) + x * y; }\n"
      "der(f, x)\n"
      "var g = function(x, y) { 2 * (x + der(f, y)); } ## der(f, y) is a "
      "matrix\n"
      "var r{3}; ## Vector of three elements\n"
      "var J{12, 12}; ## Matrix of 12x12 elements\n"
      "var dot = function(u{:}, v{:}) -> scalar {\n"
      "          return u[i] * v[i]; ## Einstein notation\n"
      "}\n"
      "var norm = function(u{:}) -> scalar { return sqrt(dot(u, u)); }\n"
      "<end>";
  
  auto arithmetic_test = 
    "(3 + 3) / (5 / (7 + 2))"
    "<end>";

    TreeParser parser(arithmetic_test);
    std::unique_ptr<Node> root = parser.parse();
    Visualizer* vis = new Visualizer(root.get());
    vis -> display(root.get(), 0, "");
}
