#pragma once

#include "tokens.hpp"
#include "ast.hpp"
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <initializer_list>

namespace lang
{
    using Expr_ptr = std::unique_ptr<Expr>;
    using Stmt_ptr = std::unique_ptr<Stmt>;
    using Type_ptr = std::unique_ptr<Type>;

    enum class Precedence
    {
        NONE,
        COMMA, // ,
        ASSIGNMENT, // = += -= == ETC
        TERNARY, // ? :
        LOGICAL_OR, // ||
        LOGICAL_AND, // &&
        BITWISE_OR, // |
        BITWISE_XOR, // ^
        BITWISE_AND,
        EQUALITY,
        COMPARISON,
        SHIFT,
        TERM,
        FACTOR,
        UNARY,
        POSTFIX // () []

    };
    class Parser
    {
    public:
        explicit Parser(const std::vector<Token>& tokens);
        std::vector<Stmt_ptr> parse();
    private:
        const std::vector<Token>& tokens;
        size_t current = 0;
        using Prefix_fn = Expr_ptr(Parser::*)();
        using Infix_fn = Expr_ptr(Parser::*)(Expr_ptr left);
        std::unordered_map<TokenType, Prefix_fn> prefix_plts;
        std::unordered_map<TokenType, Infix_fn> infix_plts;
        Token advance();
        const Token& peek() const;
        const Token& previous() const;
        bool is_at_end() const;
        bool check(TokenType type) const;
        bool match(std::initializer_list<TokenType> types);
        Token consume(TokenType type , const std::string& message);
        void error(const Token& token , const std::string& message);
        void synchronize();
        void register_plts();
        Expr_ptr parse_expression(Precedence precedence = Precedence::NONE);
        Precedence get_precedence(TokenType type) const;
        Expr_ptr parse_literal();
        Expr_ptr parse_identifier();
        Expr_ptr parse_grouping();
        Expr_ptr parse_unary();
        Expr_ptr parse_cast_or_grouping();
        Expr_ptr parse_new();//class
        Expr_ptr parse_initializer_list();//{}
        Expr_ptr parse_binary_op(Expr_ptr left);
        Expr_ptr parse_comparison_op(Expr_ptr left);
        Expr_ptr parse_logical_op(Expr_ptr left);
        Expr_ptr parse_bitwise_op(Expr_ptr left);
        Expr_ptr parse_assignment_op(Expr_ptr left);
        Expr_ptr parse_ternary_op(Expr_ptr left);
        Expr_ptr parse_call_op(Expr_ptr left);
        Expr_ptr parse_subscript_op(Expr_ptr left);
        Expr_ptr parse_member_access(Expr_ptr left);
        Type_ptr parse_type();
        Type_ptr parse_normal_type(TokenType generic_type);
        Stmt_ptr parse_declaration();
        Stmt_ptr parse_class_decl();
        Stmt_ptr parse_func_decl();
        Stmt_ptr parse_var_decl();
        void parse_class_body(std::vector<std::unique_ptr<Stmt>>& members);
        Stmt_ptr parse_class_member();
        Access_level parse_access_specifier();
        Stmt_ptr parse_stmt();
        Stmt_ptr parse_block();
        Stmt_ptr parse_if_stmt();
        Stmt_ptr parse_while_stmt();
        Stmt_ptr parse_do_while_stmt();
        Stmt_ptr parse_for_stmt();
        Stmt_ptr parse_switch_stmt();
        Stmt_ptr parse_return_stmt();
        Stmt_ptr parse_break_stmt();
        Stmt_ptr parse_continue_stmt();
        Stmt_ptr parse_print_stmt();
        Stmt_ptr parse_expression_stmt();
        Stmt_ptr parse_include_stmt();
        std::vector<Param> parse_parameter_list();
        std::vector<Expr_ptr> parse_argument_list();
        std::string parse_include_target();
        Foreign_lang parse_foreign_lang();
        Expr_ptr parse_primary();
        Expr_ptr parse_prefix();
        Expr_ptr parse_infix(Expr_ptr left);
        size_t mark() const;
        void rollback(size_t position);
        Expr_ptr parse_scope_resolution(Expr_ptr left);
        Stmt_ptr parse_empty_stmt();









    };


}