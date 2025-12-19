#pragma once
#include <string>
#include <utility>

enum class TokenType {
    Left_Karen,//"(" 
    Right_Karen,//")"
    Left_Curly_Brace, 
    Right_Curly_Brace,
    Left_Box_Brace,
    Right_Box_Brace,
    Comma, 
    Dot, 
    SemiColon,
    Colon,
    Niche_ka_part,//"%"
    Addition,//"+" 
    Subtraction,//"-" 
    Taare,//"*"
    Inclined_Tower,//"/"
    Take_Me,//"=" 
    Not,//"!"
    Chota,//"<"
    Bada,//">"
    Same_Same,//"=="
    Not_same,//"!="
    Smaller_or_same,//<="smaller equal to"
    Bigger_or_same,//>="greater equal to"
    Aadhar,//identify of variables or constans anything
    Num,
    String,
    Assume,//let
    Function,
    Agar,//if
    Nhi_Tou,//else
    Until,//while
    Give_Back,//return
    Dikhao,//print
    Add_and_TakeMe,//"+="
    Sub_and_TakeMe,//"-="
    Mul_and_TakeMe,//"*="
    Div_and_TakeMe,//"/="
    Couples,//"&&"
    Twin_Tower,//"||"
    Sach,//true
    Jhoot,//false
    Khaali,//null, none, nothing
    Breakup,//break
    Patchup,//continue
    For, //loop
    Switch,
    Case,
    Default,
    Int_Type,
    Bool_Type,
    Float_Type,
    Break_Point//end of the file 
};
struct Token {
    TokenType type;
    std::string pickme;   
    int line;             
    Token(TokenType t, std::string  me, int ln)
        : type(t), pickme(std::move(me)), line(ln) {}
};
