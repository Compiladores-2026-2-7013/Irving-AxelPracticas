%{
  #include <iostream>
  using namespace std;
%}

%option c++
%option noyywrap


digito [0-9]
letra [a-zA-Z]
palabra {letra}+
espacio [ \t\n]
/*agregamos los nuestros*/
hex_digito [0-9a-fA-F]
reservada {"if","else","while","for","int"}
hexadecimal "0"[xX]{hex_digito}+
identificador{letra}({letra}|{digito}){0,31}

%%

{espacio} {/* La acción léxica puede ir vacía si queremos que el escáner ignore la regla*/}
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
{palabra} { std::cout << "Encontré una palabra: " << yytext << std::endl; }
{identificador} { std::cout << "Identificador valido: " << yytext << std::endl; }
{hexadecimal} { std::cout << "Numero hexadecimal: " <<yytext << std::endl; }
%%


int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}
