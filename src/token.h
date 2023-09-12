#pragma once

#include <string>

class Token {

    public:
        enum class Type { //Token Type
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

        //Method definitions
        Token(Type type);
        Token(Type type, const char*beg, std::size_t len) noexcept;
        Token(Type type, const char* beg, const char* end) noexcept;
        Type get_type() const noexcept;
        void set_type(Type newtype) noexcept;
        bool is(Type type) const noexcept;
        bool is_not(Type type) const noexcept;
        bool is_one_of(Type type, Type type2) const noexcept;
        template <typename... Ts>
        bool is_one_of(Type t1, Type t2, Ts... ks) const noexcept;
        std::string_view get_lexeme() const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Type& type);





    
    private:
        Type ttype{}; //Token type
        std::string_view lexeme; //Lexeme (the actual string)


};