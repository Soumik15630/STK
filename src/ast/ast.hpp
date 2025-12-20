#pragma once

#include "tokens.hpp"
#include <vector>
#include <memory>
#include <string>
#include <optional>

struct Block_stmt;
struct Var_stmt;
struct Func_stmt;
struct Expr_stmt;
struct If_stmt;
struct For_stmt;
struct While_stmt;
struct Do_while_stmt;
struct Return_stmt;
struct Switch_stmt;
struct Print_stmt;
struct Break_stmt;
struct Continue_stmt;
struct Binary_expr;
struct Logical_expr;
struct Unary_expr;
struct Literal_expr;
struct Variable_expr;
struct Assign_expr;
struct Call_expr;
struct Array_expr;
struct Index_expr;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(Block_stmt& stmt) = 0;
    virtual void visit(Var_stmt& stmt) = 0;
    virtual void visit(Func_stmt& stmt) = 0;
    virtual void visit(Expr_stmt& stmt) = 0;
    virtual void visit(If_stmt& stmt) = 0;
    virtual void visit(For_stmt& stmt) = 0;
    virtual void visit(Do_while_stmt& stmt) = 0;
    virtual void visit(While_stmt& stmt) = 0;
    virtual void visit(Return_stmt& stmt) = 0;
    virtual void visit(Switch_stmt& stmt) = 0;
    virtual void visit(Print_stmt& stmt) = 0;
    virtual void visit(Break_stmt& stmt) = 0;
    virtual void visit(Continue_stmt& stmt) = 0;
    virtual void visit(Binary_expr& expr) = 0;
    virtual void visit(Logical_expr& expr) = 0;
    virtual void visit(Unary_expr& expr) = 0;
    virtual void visit(Literal_expr& expr) = 0;
    virtual void visit(Variable_expr& expr) = 0;
    virtual void visit(Assign_expr& expr) = 0;
    virtual void visit(Call_expr& expr) = 0;
    virtual void visit(Array_expr& expr) = 0;
    virtual void visit(Index_expr& expr) = 0;

};

struct Stmt
{
    virtual ~Stmt() = default;
    virtual void accept(Visitor& v) = 0;
};

struct Expr
{
    virtual ~Expr() = default;
    virtual void accept(Visitor& v) = 0;
};

struct Block_stmt : Stmt
{
    std::vector<std::unique_ptr<Stmt>> statements;
    Block_stmt(std::vector<std::unique_ptr<Stmt>> statement) : statements(std::move(statement)) {}
    void accept(Visitor& v) override {v.visit(*this);}
};

struct Var_stmt : Stmt
{
    Token name;
    std::optional<Token> Type;
    std::unique_ptr<Expr> initializer;

    Var_stmt(Token n , std::optional<Token> t , std::unique_ptr<Expr> init) : name(std::move(n)) , Type(std::move(t)), initializer(std::move(init)){}
    void accept(Visitor& v) override {v.visit(*this);}

};
struct Func_stmt : Stmt
{
    Token name;
    std::vector<Token> params;
    std::vector<std::unique_ptr<Stmt>> body;
    Func_stmt(Token n , std::vector<Token> p , std::vector<std::unique_ptr<Stmt>> b) : name(std::move(n)), params(std::move(p)) , body(std::move(b)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Expr_stmt : Stmt
{
    std::unique_ptr<Stmt> expression;
    Expr_stmt(std::unique_ptr<Stmt> e) : expression(std::move(e)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct If_stmt : Stmt
{
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;
    std::unique_ptr<Stmt> else_branch;

    If_stmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> b) : condition(std::move(c)), body(std::move(b)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct While_stmt : Stmt
{
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;

    While_stmt(std::unique_ptr<Expr> c , std::unique_ptr<Stmt> b) : condition(std::move(c)), body(std::move(b)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Do_while_stmt : Stmt
{
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;

    Do_while_stmt(std::unique_ptr<Expr> c , std::unique_ptr<Stmt> b) : condition(std::move(c)), body(std::move(b)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct For_stmt : Stmt
{
    std::unique_ptr<Stmt> initializer;
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Expr> increment_decrement;
    std::unique_ptr<Stmt> body;

    For_stmt(std::unique_ptr<Stmt> i, std::unique_ptr<Expr> c, std::unique_ptr<Expr> j, std::unique_ptr<Stmt> b ) : initializer(std::move(i)),condition(std::move(c)), increment_decrement(std::move(j)) , body(std::move(b)){}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Switch_Case
{
    std::vector<std::unique_ptr<Expr>> values;
    std::vector<std::unique_ptr<Stmt>> body;

    Switch_Case(std::vector<std::unique_ptr<Expr>> vals, std::vector<std::unique_ptr<Stmt>> b) : values(std::move(vals)), body(std::move(b)) {}
};

