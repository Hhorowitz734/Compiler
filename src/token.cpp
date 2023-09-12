#include "token.h"

//Constructor (sets token type)
Token::Token(Token::Type type) : ttype{type} {};

//Constructor (given beginning and string size)
Token::Token(Type type, const char*beg, std::size_t len) noexcept
    : ttype{type}, lexeme(beg, len) {};

//Constructor (given beginning and end)
Token::Token(Type type, const char* beg, const char* end) noexcept
    :ttype{type}, lexeme(beg, std::distance(beg, end)) {};


//Getters/setters for class private methods
Token::Type Token::get_type() const noexcept { return ttype; }
void Token::set_type(Type newtype) noexcept { ttype = newtype; }

//Comparison methods
bool Token::is(Type type) const noexcept { return ttype == type; }
bool Token::is_not(Type type) const noexcept {return ttype != type; }
bool Token::is_one_of(Type type, Type type2) const noexcept { return is(type) || is(type2); }

template <typename... Ts>
bool Token::is_one_of(Type t1, Type t2, Ts... ks) const noexcept {
    return is(t1) || is_one_of(t2, ks...); //Note the recursive call
}

//Lexeme getter
std::string_view Token::get_lexeme() const noexcept { return lexeme; }

#include <iomanip>
#include <iostream>

//Overloads << operator to print the token type 
std::ostream& operator<<(std::ostream& os, const Token::Type& type) {
  static const char* const names[]{
      "Number",      "Identifier",  "LeftParen",  "RightParen", "LeftSquare",
      "RightSquare", "LeftCurly",   "RightCurly", "LessThan",   "GreaterThan",
      "Equal",       "Plus",        "Minus",      "Asterisk",   "Slash",
      "Hash",        "Dot",         "Comma",      "Colon",      "Semicolon",
      "SingleQuote", "DoubleQuote", "Comment",    "Pipe",       "End",
      "Unexpected",
  };
  return os << names[static_cast<int>(type)];
}