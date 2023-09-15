#include "lexer.h"
#include "token.h"
#include "parser.h"

//g++ -std=c++17 main.cpp parser.cpp lexer.cpp token.cpp -o main

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
    "((5 / 2) * (3 / 2)) - 1"
    "<end>";

    Parser parser(arithmetic_test);
    parser.parse();
}
