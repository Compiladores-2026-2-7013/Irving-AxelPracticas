%{
#include <stdio.h>
#include <stdlib.h>

long suma_total = 0;
%}


%option noyywrap

%%

0b[01]+ {
            /* yytext + 2 salta el prefijo "0b" para la conversión */
            long valor = strtol(yytext + 2, NULL, 2);
            suma_total += valor;
            printf("Binario detectado: %s (Decimal: %ld)\n", yytext, valor);
        }

[ \t\n]+ { /* Ignorar espacios, tabuladores y saltos de línea */ }

.       { /* Ignorar cualquier otro char individual */ }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error al abrir el archivo");
            return 1;
        }
    }

    yylex();

    printf("----------------------------------\n");
    printf("Suma total en base 10: %ld\n", suma_total);
    printf("----------------------------------\n");

    return 0;
}