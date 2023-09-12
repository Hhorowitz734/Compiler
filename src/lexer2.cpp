#include "lexer.h";
#include "token.h"

Lexer::Lexer(const char* begin) noexcept : beg{begin} {};

bool Lexer::is_space(char c) noexcept {
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

bool Lexer::is_digit(char c) noexcept {
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

bool Lexer::is_identifier_char(char c) noexcept {
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

//Atom (smallest possible token -> creates 1 byte token)
Token Lexer::atom(Token:: Type type) noexcept { 
    Token t = Token(type, beg, 1);
    beg++;
    return t;
}

char Lexer::peek() const noexcept { return *beg; } //See the next character without moving pointer
char Lexer::get() noexcept { return *beg++; } //Returns current char and moves to next one


Token Lexer::next() noexcept {

    while (is_space(peek())) get(); //While there are spaces, moves through them

    switch(peek()){
        case '\0':
            return Token(Token::Type::End, beg, 1);
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
            return identifier();
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
            return number();
        case '(':
            return atom(Token::Type::LeftParen); //Since (, ) etc are one character, they have 'atoms' assigned to them
        case ')':
            return atom(Token::Type::RightParen);
        case '[':
            return atom(Token::Type::LeftSquare);
        case ']':
            return atom(Token::Type::RightSquare);
        case '{':
            return atom(Token::Type::LeftCurly);
        case '}':
            return atom(Token::Type::RightCurly);
        case '<':
            return atom(Token::Type::LessThan);
        case '>':
            return atom(Token::Type::GreaterThan);
        case '=':
            return atom(Token::Type::Equal);
        case '+':
            return atom(Token::Type::Plus);
        case '-':
            return atom(Token::Type::Minus);
        case '*':
            return atom(Token::Type::Asterisk);
        case '/':
            return atom(Token::Type::Slash);
        case '#':
            return hash_or_comment();
        case '.':
            return atom(Token::Type::Dot);
        case ',':
            return atom(Token::Type::Comma);
        case ':':
            return atom(Token::Type::Colon);
        case ';':
            return atom(Token::Type::Semicolon);
        case '\'':
            return atom(Token::Type::SingleQuote);
        case '"':
            return atom(Token::Type::DoubleQuote);
        case '|':
            return atom(Token::Type::Pipe);
        default:
            return atom(Token::Type::Unexpected); //Case that token is not any of others
    }

}

//Tokenizer mechanics
Token Lexer::identifier() noexcept {
    const char* start = beg; //Saves a pointer to the beginning
    get(); //Gets next character 
    while (is_identifier_char(peek())) get(); //Iterates while identifier is going
    return Token(Token::Type::Identifier, start, beg); //Returns the identifier as a token
}

Token Lexer::number() noexcept {
    const char* start = beg;
    get();
    while (is_digit(peek())) get();
    return Token(Token::Type::Number, start, beg);
}

Token Lexer::hash_or_comment() noexcept{
    const char* start = beg;
    get();
    if(peek() == '#'){
        get();
        start = beg;
        while (peek() != '\0'){ //Waits for newline
            if (get() == '\n') { 
                return Token( //Returns a token that encompasses the whole comment with the exception of the '##'
                    Token::Type::Comment, 
                    start, 
                    std::distance(start, beg) - 1
                    );
            }
        }
        return Token(Token::Type::Unexpected, beg, 1);
    } else {
        return Token(Token::Type::Hash, start, 1);
    }
}

