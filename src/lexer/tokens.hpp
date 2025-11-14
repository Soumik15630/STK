#pragma once
#include <string>

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
    Addition,//"+" 
    Subtraction,//"-" 
    Taare,//"*"
    Inclined_Tower,//"/"
    Take_Me,//"=" 
    Huh,//"!"
    Chota,//"<"
    Bada,//">"
    Same_Same,//"=="
    Huh_same,//"!="
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
    See,//print
    Add_and_TakeMe,//"+="
    Sub_and_TakeMe,//"-="
    Mul_and_TakeMe,//"*="
    Div_and_TakeMe,//"/="
    Couples,//"&&"
    Twin_Tower,//"||"
    Sach,//true
    Jhoot,//false
    Khaali,//null, none, nothing
    Niche_ka_part,//"%"
    Breakup,//break
    Patchup,//continue
    For, //loop
    Switch,
    Case,
    Default_It,
    Int_Type,
    String_Type,
    Bool_Type,
    Float_Type, 
    Break_Point//end of the file 
};
struct Token {
    TokenType type;
    std::string pickme;   
    int line;             
    Token(TokenType t, const std::string& me, int ln)
        : type(t), pickme(me), line(ln) {}
};
