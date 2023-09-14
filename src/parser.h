#include <string>
#include "lexer.h"
#include "token.h"

class Parser {

    private:
        std::string source_code; //Stores the code
        Lexer lexer;
        Token curr_token;

        //To allow the peek function to work
        bool has_peeked = false;
        Token next_token;

    public:
        
        //Default constructor
        Parser(const std::string& code) noexcept;

        //Advance + Consume + Peek methods
        void advance() noexcept;
        void consume(Token::Type expected_type);
        Token peek() noexcept;

        //Parse
        void parse() noexcept;

        //Prints token
        void print_token(const Token& token) noexcept;

        //Expression management
        double expr() noexcept;
        double factor();
        double term() noexcept;

        //Helper methods
        double sv_to_double(std::string_view stringview);





};