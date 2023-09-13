#include <string>
#include "lexer.h"
#include "token.h"

class Parser {

    private:
        std::string source_code; //Stores the code
        Lexer lexer;
        Token curr_token;

    public:
        
        //Default constructor
        Parser(const std::string& code) noexcept;

        //Advance
        void advance() noexcept;
        
        //Parse
        void parse() noexcept;

        //Process token
        void process_token(const Token& token) noexcept;





};