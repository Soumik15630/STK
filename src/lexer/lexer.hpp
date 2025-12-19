#pragma once
#include "tokens.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

class Lexer
{
public:
    Lexer(std::string_view source);
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
    [[nodiscard]] bool is_at_end() const;
    char advance();       // advances the current index
    [[nodiscard]] char peek() const;          // jst to chk
    [[nodiscard]] char peek_next() const;     // 2 step ahd
    bool same(char ex); // check with the expected character
    void skip_whitespaces_and_comments();
    void string_literal(); // reads the entire string until the closing
    void number();
    void identifier();
    void add_token(TokenType type);
    void add_token_literal(TokenType type,   std::string_view me);
    void add_token_string(TokenType type,     std::string&& me);
    void report_error(const std::string &message);
};