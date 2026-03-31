%{
#include <stdio.h>
#include <ctype.h> // Necesaria para la función toupper

void convertir_a_mayusculas(char *str);
%}


%option noyywrap

%%

[a-z]+  { 
            /* Detecta una secuencia de letras min */
            convertir_a_mayusculas(yytext);
            fprintf(yyout, "%s", yytext); 
        }

.|\n    { 
            /* Cualquier otro char (espacios, num, saltos) 
               se copia tal cual a la salida */
            fprintf(yyout, "%s", yytext); 
        }

%%

void convertir_a_mayusculas(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Error al abrir entrada");
        return 1;
    }

    FILE *salida = fopen(argv[2], "w");
    if (!salida) {
        perror("Error al crear salida");
        fclose(entrada);
        return 1;
    }

    yyin = entrada;
    yyout = salida;

    yylex();

    fclose(entrada);
    fclose(salida);

    printf("El proceso finalizo con exito. Favor de revisar el archivo de salida: %s\n", argv[2]);
    return 0;
}