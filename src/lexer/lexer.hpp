#pragma once
#include "tokens.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class Lexer
{
public:
    Lexer(const std::string_view source);
    std::vector<Token> tokenize();

private:
    std::string_view src;
    std::vector<Token> tokens; // token bucket
    size_t start = 0;          // indexing current token
    size_t current_index = 0;
    int line = 1; // line number
    bool had_error = false;
    static const std::unordered_map<std::string_view, TokenType> keywords;

    void scan_token();
    bool is_at_end();
    char advance();       // advancecs the current index
    char peek();          // jst to chk
    char peek_next();     // 2 step ahd
    bool same(char expt); // check with the expected character
    void skip_whitespaces_and_comments();
    void string_literal(); // reads the entire string until the closing"
    void number();
    void identifier();
    void add_token(TokenType type);
    void add_token(TokenType type, const std::string_view me);
    void add_token(TokenType type, const std::string &me);
    void report_error(const std::string &message);
};