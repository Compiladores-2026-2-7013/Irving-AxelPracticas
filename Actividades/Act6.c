%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int suma_actual = 0;
char linea_aux[1024]; // Buffer para reconstruir la línea si termina en B
%}

%option noyywrap

%%

[0-9]+      {
                /* Sumamos el valor de num */
                suma_actual += atoi(yytext);
                /* Guardamos el texto en nuestro buffer temporal */
                strcat(linea_aux, yytext);
            }

[ \t]+      {
                /* Preservamos los espacios en el buffer */
                strcat(linea_aux, yytext);
            }

"A"         {
                /* Si termina en A, imprimimos la suma acumulada */
                printf("%d\n", suma_actual);
            }

"B"         {
                /* Si termina en B, imprimimos la línea original guardada */
                printf("%sB\n", linea_aux);
            }

\n          {
                /* Al final de cada line  reseteamos  */
                suma_actual = 0;
                linea_aux[0] = '\0';
            }

.           { /* Ignorar cualquier otro carácter */ }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error al abrir el archivo");
            return 1;
        }
    }
    
    // Inicializar buffer
    linea_aux[0] = '\0';
    
    yylex();
    return 0;
}