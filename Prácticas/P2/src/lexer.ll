%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line = 1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT})*
NUM        {DIGIT}+(\.{DIGIT}+)?

%%

/* ====== PALABRAS RESERVADAS ====== */

"int"        { return t_int; }
"float"      { return t_float; }
"if"         { return t_if; }
"else"       { return t_else; }
"while"      { return t_while; }

/* ====== IDENTIFICADORES Y NUMEROS ====== */

{ID}         { return t_id; }
{NUM}        { return t_num; }

/* ====== OPERADORES ====== */

"+"          { return t_plus; }
"-"          { return t_minus; }
"*"          { return t_mul; }
"/"          { return t_div; }

/* ====== SIMBOLOS ====== */

"="          { return t_assign; }
";"          { return t_semi; }
","          { return t_comma; }

"("          { return t_lparen; }
")"          { return t_rparen; }

/* ====== ESPACIOS ====== */

[ \t\r]+     { /* ignorar */ }
"\n"         { line++; }

/* ====== ERROR ====== */

.            { 
               cout << "ERROR LEXICO: " << yytext 
                    << " en linea " << line << endl; 
             }

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine(){
    return line;
}