%{
#include <stdio.h>

int lineas = 0;
int palabras = 0;
int bytes = 0;
%}


%option noyywrap

%%

\n          { lineas++; bytes++; }
[^\t\n ]+   { palabras++; bytes += yyleng; }
.           { bytes++; }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror("Error al abrir el archivo");
            return 1;
        }
        yyin = f;
    }

    yylex();

    /* Imprime el resultado al estilo del comando wc: líneas, palabras, bytes */
    printf("%d %d %d\n", lineas, palabras, bytes);

    return 0;
}