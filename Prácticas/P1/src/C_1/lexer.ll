%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive


DIG [0-9]
NMBR {DIG}+(\.{DIG}+)?([eE][+-]?{DIG}+)?
WRD [a-zA-Z]
SPACE [\t]+
ID ({WRD}|_)({WRD}|{DIG}|_){0,31}

%%

"int" {return C_1::INT;}
"float" {return C_1::FLOAT;}
"if" {return C_1::IF;}
"else" {return C_1::ELSE;}
"while" {return C_1::WHILE;}

"+" {return C_1::MAS;}
"-" {return C_1::MENOS;}
"*" {return C_1::MULT;}
"/" {return C_1::DIV;}
"=" {return C_1::EQUAL;}
"[" {return C_1::LCOR;}
"]" {return C_1::RCOR;}
"(" {return C_1::LPAR;}
")" {return C_1::RPAR;}
"," {return C_1::COMA;}
";" {return C_1::PYCOMA;}

{NUMBER}    { return C_1::NUMERO; }
{ID}        { return C_1::ID; }


.   { cout << "ERROR LEXICO" << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

