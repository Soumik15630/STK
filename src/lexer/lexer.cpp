#include <lexer.hpp>
#include <iostream>
#include <cctype>

static const std::unordered_map<std::string_view , TokenType> keywords ={
    {"let" , TokenType::Assume},
    {"function" , TokenType::Function},
    {"if", TokenType::Agar},
    {"else", TokenType::Nhi_Tou},
    {"while", TokenType::Until},
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
    {"string", TokenType::String_Type},
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
    char c = advance();
    switch(c){
        
        case '(' : add_token(TokenType::Left_Karen); break;
        case ')' : add_token(TokenType::Right_Karen); break;
        case '{' : add_token(TokenType::Left_Curly_Brace); break;
        case '}' : add_token(TokenType::Right_Curly_Brace); break;
        case '[' : add_token(TokenType::Left_Box_Brace); break;
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
            if (isdigit(c)){
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
        char c = peek();
        switch (c){
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
                    while(!is_at_end() && peek()=='/'){
                        advance();
                    }

                }else if (peek_next()== '*'){
                    advance();
                    advance(); // consuming '/*'
                    while (!is_at_end()){
                        if (peek()=='\n'){
                            line++;
                        }else if (peek() == '*' && peek_next() == '/'){
                            advance();
                            advance();
                            break;
                        }
                        advance();
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
    while (isalnum(peek() || peek()== '_')){
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
    while (isdigit(peek())){
        advance();
        if (peek()=='.' && isdigit(peek_next())){
            advance();
            while (isdigit(peek())){
                advance();
            }
        }
        if (peek() == 'e' || peek() == 'E'){
            advance();
            if (!isdigit(peek())){
                report_error("Expected exponent.");

            }
            while(isdigit(peek())){
                advance();
            }
        }
        add_token(TokenType::Num , src.substr(start, current_index-start));
    }

}


