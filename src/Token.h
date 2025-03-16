#include <string>
#include <variant>
#include "TokenType.h"

using namespace std;
typedef variant<double, string> Literal

class Token {
    public:
        const TokenType type;
        const string lexeme;
        const Literal literal;
        const int line;

        Token(TokenType type, string lexeme, Literal literal, int line):
            type(type), lexeme(lexeme), literal(literal), line(line) {}
            
        /* toString aqui */

};