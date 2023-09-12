#include <string>

//A majority of this project is not currently my original code
//Please see https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20
//I am currently tinkering with this lexer code to see if i can make a compiler


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

        //Constructor (sets token type)
        Token(Type type) : ttype{type} {};

        //Constructor (given beginning and string size)
        Token(Type type, const char*beg, std::size_t len) noexcept
            : ttype{type}, lexeme(beg, len) {};
        
        //Constructor (given beginning and end)
        Token(Type type, const char* beg, const char* end) noexcept
            :ttype{type}, lexeme(beg, std::distance(beg, end)) {};


        //Getters/setters for class private methods
        Type get_type() const noexcept { return ttype; }
        void set_type(Type newtype) noexcept { ttype = newtype; }

        //Comparison methods
        bool is(Type type) const noexcept { return ttype == type; }
        bool is_not(Type type) const noexcept {return ttype != type; }
        bool is_one_of(Type type, Type type2) const noexcept { return is(type) || is(type2); }

        template <typename... Ts>
        bool is_one_of(Type t1, Type t2, Ts... ks) const noexcept {
            return is(t1) || is_one_of(t2, ks...); //Note the recursive call
        }

        //Lexeme getter
        std::string_view get_lexeme() const noexcept { return lexeme; }
    
    private:
        Type ttype{}; //Token type
        std::string_view lexeme; //Lexeme (the actual string)


};

class Lexer {
    public:
        Lexer(const char* begin) noexcept : beg{begin} {}; //Constructor

       
    
    private:
        const char* beg = nullptr; //Pointer to a constant character (beginning of string)

        //Forward declarations of critical methods
        Token identifier() noexcept;
        Token number() noexcept;
        Token slash_or_comment() noexcept;
        Token atom(Token::Type) noexcept;

        char peek() const noexcept { return *beg; } //See the next character without moving pointer
        char get() noexcept { return *beg++; } //Returns current char and moves to next one

        //Cheker functions
        bool is_space(char c) noexcept { //Noexcept doesn't throw exceptions, but this can be a performance boost in functions that are used often
            switch(c){
                case ' ':
                case '\t':
                case '\r':
                case '\n': //Newline counts as a space
                    return true;
                default:
                    return false;
            }
        }

        bool is_digit(char c) noexcept {
            switch(c){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    return true;
                default:
                    return false;
            }
        }

        bool is_identifier_char(char c) noexcept {
            switch(c){
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '_':
                case '?': //This would allow variables to have ? in them
                    return true;
                default:
                    return false;
            }
        }

};