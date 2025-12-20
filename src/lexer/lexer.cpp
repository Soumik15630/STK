#include "lexer.hpp"
#include <iostream>
#include <cctype>


inline bool is_alpha(char c)
{
    return std::isalpha(static_cast<unsigned char>(c));
}

inline bool is_digit(char c)
{
    return std::isdigit((static_cast<unsigned char>(c)));
}

inline bool is_alnum(char c)
{
    return std::isalnum(static_cast<unsigned char>(c));
}
const std::unordered_map<std::string_view , TokenType> Lexer::keywords ={
    {"let" , TokenType::Assume},
    {"function" , TokenType::Function},
    {"if", TokenType::Agar},
    {"else", TokenType::Nhi_Tou},
    {"while", TokenType::Until},
    {"do", TokenType::Do},
    {"return", TokenType::Give_Back},
    {"print", TokenType::Dikhao},
    {"true", TokenType::Sach},
    {"false", TokenType::Jhoot},
    {"null" , TokenType::Khaali},
    {"break", TokenType::Breakup},
    {"continue", TokenType::Patchup},
    {"for", TokenType::For},
    {"switch", TokenType::Switch},
    {"case", TokenType::Case},
    {"default", TokenType::Default},
    {"int", TokenType::Int_Type},
    {"string", TokenType::String},
    {"bool", TokenType::Bool_Type},
    {"float", TokenType::Float_Type}

};

Lexer::Lexer(const std::string_view source) : src(source){}

std::vector<Token> Lexer::tokenize(){
    while (!is_at_end()){
        skip_whitespaces_and_comments();
        if (is_at_end()){break;}
        start = current_index;
        scan_token();
    }
    
    tokens.emplace_back(TokenType::Break_Point, ".....", line);
    return tokens;
    
}

void Lexer::scan_token(){
    switch(const char c = advance()){
        
        case '(' : add_token(TokenType::Left_Karen); break;
        case ')' : add_token(TokenType::Right_Karen); break;
        case '{' : add_token(TokenType::Left_Curly_Brace); break;
        case '}' : add_token(TokenType::Right_Curly_Brace); break;
        case '[' : add_token(TokenType::Left_Box_Brace); break;
        case ']' : add_token(TokenType::Right_Box_Brace); break;
        case ',' : add_token(TokenType::Comma); break;
        case '.' : add_token(TokenType::Dot); break;
        case ';' : add_token(TokenType::SemiColon); break;
        case ':' : add_token(TokenType::Colon); break;
        case '%' : add_token(TokenType::Niche_ka_part); break;
        case '+' : add_token(same('=') ? TokenType::Add_and_TakeMe : TokenType::Addition); break;
        case '-' : add_token(same('=') ? TokenType::Sub_and_TakeMe : TokenType::Subtraction); break;
        case '*' : add_token(same('=') ? TokenType::Mul_and_TakeMe : TokenType::Taare); break;
        case '/' : add_token(same('=') ? TokenType::Div_and_TakeMe : TokenType::Inclined_Tower); break;
        case '=' : add_token(same('=') ? TokenType::Same_Same : TokenType::Take_Me); break;
        case '!' : add_token(same('=') ? TokenType::Not_same : TokenType::Not); break;
        case '<' : add_token(same('=') ? TokenType::Smaller_or_same : TokenType::Chota); break;
        case '>' : add_token(same('=') ? TokenType::Bigger_or_same : TokenType::Bada); break;
        case '&' : 
            if (same('&')){
                add_token(TokenType::Couples);
            }
            else {
                report_error("Unexpected Character '&'.");
            }
            break;
        case '|' : 
            if (same('|')){
                add_token(TokenType::Twin_Tower);
            }
            else {
                report_error("Unexpected Character '|'.");
            }
            break;
        case '"' : string_literal(); break;
        
        default : 
            if (is_digit(c)){
                number();
            }else if (isalpha(c) || c == '_' ){
                identifier();
            }
            else{
                report_error("Unexpected Character.");
            }
            break;
    }

}

void Lexer::skip_whitespaces_and_comments(){
    while (true){
        switch (peek()){
            case ' ' :
            case '\r' :
            case '\t' :
                advance();
                break;
            case '\n' : 
                line++ ;
                advance();
                break;
            case '/' :
                if (peek_next()=='/'){
                    while(!is_at_end() && peek()!='\n'){
                        advance();
                    }

                }else if (peek_next()== '*'){
                    advance();
                    advance(); // consuming '/*'
                    bool closed = false;
                    while (!is_at_end()){
                        if (peek()=='\n'){
                            line++;
                        }else if (peek() == '*' && peek_next() == '/'){
                            advance();
                            advance();
                            closed = true;
                            break;
                        }
                        advance();
                    }
                        if (!closed)
                        {
                            report_error(("Unterminated Block Comment."));
                        }

                }else {
                    return;
                }
                break;
            default : return;
        }
    }
    
}
 
void Lexer::identifier(){
    while (is_alnum(peek()) || peek()== '_'){
        advance();
    }
    std::string_view text = src.substr(start, current_index-start);
    TokenType type = TokenType::Aadhar;
    
    auto it = keywords.find(text);
    if (it != keywords.end()){
        type = it->second;

    }
    add_token(type);
}

void Lexer::number(){
    while (is_digit(peek()))
    {
        advance();
    }
        if (peek()=='.' && is_digit(peek_next())){
            advance();
            while (is_digit(peek())){
                advance();
            }
        }
        if (peek() == 'e' || peek() == 'E'){
            advance();
            if (peek() == '+' || peek() == '-')
            {
                advance();
            }
            if (!is_digit(peek())){
                report_error("Expected exponent.");

            }
            while(is_digit(peek())){
                advance();
            }
        }
        add_token_literal(TokenType::Num , src.substr(start, current_index-start));


}

void Lexer::string_literal(){
    std::string value = "";

    while (peek()!= '"' && !is_at_end()){
        if (peek()=='\n'){
            line++;
        }
        if (peek()=='\\'){
            advance();
            switch (peek()){
                case 'n' : value +='\n';break;
                case 't' : value += '\t';break;
                case 'r' : value += '\r';break;
                case '\\' : value += '\\';break;
                case '"' : value += '"';break;
            default :
                report_error(("Invalid Escape Sequence."));
                value+= peek();
                break;
            }
            advance();
        }else{
            value += advance();
        } 
        
    }
    if (is_at_end()){
        report_error("Expected ending String indentation");
        return;
    }
    advance();
    add_token_string(TokenType::String , std::move(value));
}

bool Lexer::same(char ex){
    if (is_at_end()){
        return false;
    }
    if (src[current_index]!= ex){
        return false;

    }
    current_index++;
    return true;
}
char Lexer::peek() const{
    if (is_at_end())
    {
        return '\0';
    }
    return src[current_index];
}

char  Lexer::peek_next() const
{
    if (current_index+1 >= src.length()){return '\0';}
    return src[current_index +1];
}

char Lexer::advance()
{
    return src[current_index++];
}

bool Lexer::is_at_end() const
{
    return (current_index >= src.length());
}

void Lexer::add_token(TokenType type)
{
    const std::string_view text = src.substr(start , current_index-start);
    tokens.emplace_back(type , std::string(text), line);
}

void Lexer::add_token_literal(TokenType type, const std::string_view me)
{
    tokens.emplace_back(type , std::string(me), line);
}

void Lexer::add_token_string(TokenType type,   std::string&& me)
{
    tokens.emplace_back(type , std::move(me), line);
}

void Lexer::report_error(const std::string& message)
{
    had_error = true;
    std::cerr<<"[Line" << line << "] Error : " << message << std::endl;

}



