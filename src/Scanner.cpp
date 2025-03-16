#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "error_handling.h"

using namespace std;

class Scanner { 
    private:
        string source;
        vector<Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;

        Scanner(string source) :
            source(source) {}; 

        bool isAtEnd(){
            return current >= source.size();
        }
        
        vector<Token> scanTokens(){
            while(!isAtEnd()){
                start = current;
                scanToken();
            }
            tokens.push_back(Token(TOKEN_EOF, "", string(""), line));
            return tokens;
        }

        char advance(){
            current++;
            return source[current-1];
        }

        void addToken(TokenType type){
            addToken(type, "");
        }

        void addToken(TokenType type, Literal literal){
            string text = source.substr(start,current-start);
            tokens.push_back(Token(type, text, literal, line));
        }

        bool match(char expected){
            if(isAtEnd()) return false;
            if(source[current+1] != expected) return false;
            current++;
            return true;
        }

        char peek(){
            if(isAtEnd()) return '\0';
            return source.charAt(current);
        }

        char peekNext{
            if(current+1 >= source.size()) return '\0';
            return source[current+1];
        }

        void string(){
            while(peek() != '"' && !isAtEnd()){
                if (peek() == '\n') line++;
                advance();
            }
            if(isAtEnd()){
                error(line, "Unterminated string.");
                return;
            }

            advance();

            string value = source.substr(start+1, current-1);
            addToken(STRING, Literal(value));
        }

        bool isDigit(c){
            return c >= '0' && c <= '9';
        }

        void number(){
            while(isDigit(peek())) advance();

            // Look for a fractional part.
            if(peek() == '.' && isDigit(peekNext())){
                advance();
                while(isDigit(peek())) advance();
            }
            addToken(NUMBER, stod(source.substr(start,current));
        }

        void scanToken(){
            char c = advance();
            switch(c){
                case '(': addToken(LEFT_PAREN); break;
                case ')': addToken(RIGHT_PAREN); break;
                case '{': addToken(LEFT_BRACE); break;
                case '}': addToken(LEFT_BRACE); break;
                case ',': addToken(LEFT_COMMA); break;
                case '.': addToken(LEFT_DOT); break;
                case '-': addToken(LEFT_MINUS); break;
                case '+': addToken(LEFT_PLUS); break;
                case ';': addToken(LEFT_SEMICOLON); break;
                case '*': addToken(LEFT_STAR); break;
                case '!':
                    addToken(match('=') ? BANG_EQUAL : BANG);
                    break;
                case '=':
                    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
                    break;
                case '<':
                    addToken(match('=') ? LESS_EQUAL : LESS);
                    break;
                case '>':
                    addToken(match('=') ? GREATER_EQUAL : GREATER);
                    break;
                case '/':
                    if ((match('/'))){
                        while (peek()!= '\n' && isAtEnd()) advance();
                    }else{
                        addToken(SLASH);
                    }
                    break;
                case ' ':
                case '\r':
                case '\t':
                    break;
                case '\n':
                    line++; break;
                case '"': string(); break;
                

                default : 
                    if(isDigit(c)){
                        number();
                    }else{
                        error(line, "Unexpected Character."); break;
                    }

            }
        }

};