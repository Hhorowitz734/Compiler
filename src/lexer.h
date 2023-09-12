
#include <string>
#include "token.h" // Including the Token header

class Lexer {
public:
    // Constructor
    explicit Lexer(const char* begin) noexcept;

    // Get the next token from the source
    Token next() noexcept;

private:
    const char* beg = nullptr; // Pointer to the beginning of the string

    // Method prototypes
    Token identifier() noexcept;
    Token number() noexcept;
    Token hash_or_comment() noexcept;
    Token atom(Token::Type type) noexcept;
    char peek() const noexcept;
    char get() noexcept;

    // Checker functions
    bool is_space(char c) noexcept;
    bool is_digit(char c) noexcept;
    bool is_identifier_char(char c) noexcept;
};
