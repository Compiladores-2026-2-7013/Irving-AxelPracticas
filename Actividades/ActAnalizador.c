%{
#include <stdio.h>
#include <string.h>

void imprimir_token(const char* clase, const char* valor);
void error_lexico(char c, int linea);
%}

/* Contar lineas automaticamentee */
%option yylineno
%option noyywrap

/* Estados exclusivos cadensas y Comentarios de varias lineas */
%x CADENA COMENTARIO_M

/* Definiciones Regulares como lo hemos hecho anteriormente */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
ENTERO      {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+

%%

    /* --- Comentarios de una sola linea --- */
"--".* { /* Ignorar */ }

    /* --- Comentarios de mas lineas --- */
"<*"        { BEGIN(COMENTARIO_M); }
<COMENTARIO_M>"*>" { BEGIN(INITIAL); }
<COMENTARIO_M>\n   { /* Ignorar */ }
<COMENTARIO_M>.    { /* Ignorar */ }

    /* --- Cadenas de caracteres --- */
\"          { BEGIN(CADENA); }
<CADENA>[^\"\n]* { imprimir_token("CADENA", yytext); }
<CADENA>\"  { BEGIN(INITIAL); }
<CADENA>\n  { error_lexico('\n', yylineno-1); BEGIN(INITIAL); }

    /* --- Palabras Reservadas --- */
"if"|"then"|"else"|"while"|"do"|"case"|"is"|"void"|"true"|"false"|"begin"|"end"|"not" { 
    imprimir_token("PALABRA_RESERVADA", yytext); 
}

    /* --- Identificadores --- */
{ID}        { imprimir_token("ID", yytext); }

    /* --- Nums --- */
{REAL}      { imprimir_token("NUM_REAL", yytext); }
{ENTERO}    { imprimir_token("NUM_ENTERO", yytext); }

    /* --- Operadores de Asignación y Relacionales --- */
":="        { imprimir_token("OP_ASIG", yytext); }
"<>"        { imprimir_token("OP_REL", yytext); }
">"|"<"|"=" { imprimir_token("OP_REL", yytext); }

    /* --- Operadores Aritméticos --- */
"+"|"-"|"*"|"/"|"%" { imprimir_token("OP_ARIT", yytext); }

    /* --- Símbolos Especiales --- */
"("|")"|"{"|"}"|";"|"," { imprimir_token("SIMB_ESP", yytext); }

    /* --- Espacios en blanco --- */
[ \t\n\r]+  { /* Ignorar */ }

    /* --- Errores --- */
.           { error_lexico(yytext[0], yylineno); }

%%

void imprimir_token(const char* clase, const char* valor) {
    fprintf(yyout, "<%s, %s>\n", clase, valor); 
}

void error_lexico(char c, int linea) {
    fprintf(yyout, "Error léxico: Carácter '%c' no reconocido en línea %d\n", c, linea);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s archivo.art\n", argv[0]);
        return 1;
    }

    // Validar extensión .art
    char *ext = strrchr(argv[1], '.');
    if (!ext || strcmp(ext, ".art") != 0) {
        printf("Error: El archivo debe tener el tipo de extension .art\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("Error al abrir"); return 1; }

    // Generar nombre de salida .tokens
    char nombre_salida[256];
    strncpy(nombre_salida, argv[1], ext - argv[1]);
    nombre_salida[ext - argv[1]] = '\0';
    strcat(nombre_salida, ".tokens");

    FILE *o = fopen(nombre_salida, "w");
    if (!o) { fclose(f); return 1; }

    yyin = f;
    yyout = o;

    yylex();

    fclose(f);
    fclose(o);
    printf("Tokens generados exitosamente en: %s\n", nombre_salida);

    return 0;
}