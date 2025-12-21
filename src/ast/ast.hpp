#pragma once

#include "tokens.hpp"
#include <vector>
#include <memory>
#include <string>

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
struct Primitive_type;
struct Vector_type;
struct Array_type;
struct Pointer_type;
struct Reference_type;

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

struct Type
{
    virtual ~Type() = default;
};

struct Block_stmt : Stmt
{
    std::vector<std::unique_ptr<Stmt>> statements;
    explicit Block_stmt(std::vector<std::unique_ptr<Stmt>> statement) : statements(std::move(statement)) {}
    void accept(Visitor& v) override {v.visit(*this);}
};

struct Var_stmt : Stmt
{
    Token name;
    std::unique_ptr<Type> Type;
    std::unique_ptr<Expr> initializer;

    Var_stmt(Token n , std::unique_ptr<struct Type> t , std::unique_ptr<Expr> init) : name(std::move(n)) , Type(std::move(t)), initializer(std::move(init)){}
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

struct Switch_stmt : Stmt
{
    std::unique_ptr<Expr> condition;
    std::vector<Switch_Case> cases;
    std::vector<std::unique_ptr<Stmt>> default_branch;
    Switch_stmt(std::unique_ptr<Expr> c, std::vector<Switch_Case> cs , std::vector<std::unique_ptr<Stmt>> db) : condition(std::move(c)), cases(std::move(cs)), default_branch(std::move(db)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Return_stmt : Stmt
{
    Token keyword;
    std::unique_ptr<Expr> value;
    Return_stmt(Token k, std::unique_ptr<Expr> v) : keyword(std::move(k)) , value(std::move(v)) {}

    void accept(Visitor& v) override {v.visit(*this);};
};

struct Print_stmt : Stmt
{
    std::unique_ptr<Expr> expression;
    explicit Print_stmt(std::unique_ptr<Expr> e) : expression((std::move(e))){}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Break_stmt : Stmt
{
    Token keyword;
    explicit Break_stmt(Token k) : keyword(std::move(k)){}
    void accept(Visitor& v) override {v.visit(*this);};
};
struct Continue_stmt : Stmt
{
    Token keyword;
    explicit Continue_stmt(Token k) : keyword(std::move(k)){}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Binary_expr : Expr
{
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary_expr(std::unique_ptr<Expr> l , Token o, std::unique_ptr<Expr> r) : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}
    void accept(Visitor& v) override {v.visit(*this);};

};

struct Logical_expr : Expr
{
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Logical_expr(std::unique_ptr<Expr> l , Token o , std::unique_ptr<Expr> r) : left(std::move(l)) , op(std::move(o)), right(std::move(r)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Unary_expr : Expr
{
    Token op;
    std::unique_ptr<Expr> right;
    Unary_expr(Token o , std::unique_ptr<Expr> r) : op(std::move(o)), right(std::move(r)) {}

    void accept(Visitor& v) override {v.visit(*this);};
};

struct Literal_expr : Expr
{
    std::string value;
    TokenType type;
    Literal_expr(std::string v, TokenType t ) : value(std::move(v)), type(t) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Variable_expr : Expr
{
    Token name;
    explicit Variable_expr(Token n) : name(std::move(n)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Assign_expr : Expr
{
    std::unique_ptr<Expr> target;
    Token op;
    std::unique_ptr<Expr> value;

    Assign_expr(std::unique_ptr<Expr> t, Token o, std::unique_ptr<Expr> v) : target(std::move(t)), op(std::move(o)) , value(std::move(v)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Call_expr : Expr
{
    std::unique_ptr<Expr> call;
    Token paren;//'(' token
    std::vector<std::unique_ptr<Expr>> arguments;

    Call_expr(std::unique_ptr<Expr> c, Token p, std::vector<std::unique_ptr<Expr>> a) : call(std::move(c)), paren(std::move(p)), arguments(std::move(a)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};
struct Array_expr : Expr
{
    std::vector<std::unique_ptr<Expr>> elements;
    explicit Array_expr(std::vector<std::unique_ptr<Expr>> e) : elements((std::move(e))) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Index_expr : Expr
{
    std::unique_ptr<Expr> object;
    Token bra;//'[' token
    std::unique_ptr<Expr> index;

    Index_expr(std::unique_ptr<Expr> o, Token b, std::unique_ptr<Expr> i) : object(std::move(o)), bra(std::move(b)) , index(std::move(i)) {}
    void accept(Visitor& v) override {v.visit(*this);};
};

struct Primitive_type : Type
{
    TokenType kind;
    explicit Primitive_type(TokenType k) : kind(k){}

};

struct Vector_type : Type
{
    std::unique_ptr<Type> element_type;
    explicit Vector_type(std::unique_ptr<Type> e) : element_type(std::move(e)){}


};

struct Array_type : Type
{
    std::unique_ptr<Type> element_type;
    size_t size;

    Array_type(std::unique_ptr<Type> e, size_t s) : element_type(std::move(e)), size(s) {}

};

struct Pointer_type : Type
{
    std::unique_ptr<Type> pointe;
    explicit Pointer_type(std::unique_ptr<Type> p) : pointe(std::move(p)) {}

};

struct Reference_type : Type
{
    std::unique_ptr<Type> refer;
    explicit Reference_type(std::unique_ptr<Type> r) : refer(std::move(r)) {}

};