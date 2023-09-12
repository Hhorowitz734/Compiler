#include <string>

class Token {
    public:
        enum class Kind {
            Number,
            Identifier,
            LeftParen,
            RightParen,
            LeftSquare,
            RightSquare,
            LeftCurly,
            RightCurly,
            LessThan,
            GreaterThan,
            Equal,
            Plus,
            Minus,
            Asterisk,
            Slash,
            Hash,
            Dot,
            Comma,
            Colon,
            Semicolon,
            SingleQuote,
            DoubleQuote,
            Comment,
            Pipe,
            End,
            Unexpected,
        };
};