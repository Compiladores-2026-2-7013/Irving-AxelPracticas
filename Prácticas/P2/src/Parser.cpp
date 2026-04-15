#include "headers/Parser.hpp"
#include <iostream>

using namespace std;

namespace C_1
{
  Parser::Parser(){}

  Parser::Parser(Lexer *lexer){
    this->lexer = lexer;
  }
    
  Parser::~Parser(){}

  /************************************************************************/
  /**                          PROGRAMA                                   **/
  /************************************************************************/

  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  /************************************************************************/
  /**                    FUNCIONES POR NO TERMINAL                        **/
  /************************************************************************/

  /* declaraciones → declaracion declaraciones' */
  void Parser::declaraciones(){
    if(token == t_int || token == t_float){
      declaracion();
      declaraciones_p();
    }
  }

  /* declaraciones' → declaracion declaraciones' | ε */
  void Parser::declaraciones_p(){
    if(token == t_int || token == t_float){
      declaracion();
      declaraciones_p();
    }
  }

  /* declaracion → tipo lista_var ; */
  void Parser::declaracion(){
    tipo();
    lista_var();
    if(token == t_semi)
      match(t_semi);
    else
      error("Se esperaba ;");
  }

  /* tipo → int | float */
  void Parser::tipo(){
    if(token == t_int)
      match(t_int);
    else if(token == t_float)
      match(t_float);
    else
      error("Se esperaba tipo");
  }

  /* lista_var → id lista_var' */
  void Parser::lista_var(){
    if(token == t_id){
      match(t_id);
      lista_var_p();
    } else {
      error("Se esperaba identificador");
    }
  }

  /* lista_var' → , id lista_var' | ε */
  void Parser::lista_var_p(){
    if(token == t_comma){
      match(t_comma);
      match(t_id);
      lista_var_p();
    }
  }

  /* sentencias → sentencia sentencias' */
  void Parser::sentencias(){
    sentencia();
    sentencias_p();
  }

  /* sentencias' → sentencia sentencias' | ε */
  void Parser::sentencias_p(){
    if(token == t_id || token == t_if || token == t_while){
      sentencia();
      sentencias_p();
    }
  }

  /* sentencia */
  void Parser::sentencia(){
    if(token == t_id){
      match(t_id);
      match(t_assign);
      expresion();
      match(t_semi);
    }
    else if(token == t_if){
      match(t_if);
      match(t_lparen);
      expresion();
      match(t_rparen);
      sentencias();
      sentencia_p();
    }
    else if(token == t_while){
      match(t_while);
      match(t_lparen);
      expresion();
      match(t_rparen);
      sentencias();
    }
    else{
      error("Sentencia invalida");
    }
  }

  /* sentencia' → else sentencias | ε */
  void Parser::sentencia_p(){
    if(token == t_else){
      match(t_else);
      sentencias();
    }
  }

  /* expresion → termino expresion' */
  void Parser::expresion(){
    termino();
    expresion_p();
  }

  /* expresion' */
  void Parser::expresion_p(){
    if(token == t_plus){
      match(t_plus);
      termino();
      expresion_p();
    }
    else if(token == t_minus){
      match(t_minus);
      termino();
      expresion_p();
    }
  }

  /* termino → factor termino' */
  void Parser::termino(){
    factor();
    termino_p();
  }

  /* termino' */
  void Parser::termino_p(){
    if(token == t_mul){
      match(t_mul);
      factor();
      termino_p();
    }
    else if(token == t_div){
      match(t_div);
      factor();
      termino_p();
    }
  }

  /* factor */
  void Parser::factor(){
    if(token == t_id){
      match(t_id);
    }
    else if(token == t_num){
      match(t_num);
    }
    else if(token == t_lparen){
      match(t_lparen);
      expresion();
      match(t_rparen);
    }
    else{
      error("Factor invalido");
    }
  }

  /************************************************************************/
  /**                    FUNCIONES AUXILIARES                            **/
  /************************************************************************/

  void Parser::match(Token expected){
    if(token == expected){
      token = eat();
    } else {
      error("Token inesperado");
    }
  }

  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS: " << msg 
         << " en la línea " << lexer->getLine() << endl;
    exit(1);
  }   

  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}