%{
#include <stdio.h>
#include <string.h>

char tablero[10]; // 9 casillas + fin de cadena
int indice = 0;

void evaluar_juego();
%}

%option noyywrap

%%

[XO_]   { 
            tablero[indice++] = yytext[0]; 
            if (indice == 9) {
                tablero[9] = '\0';
                evaluar_juego();
                indice = 0; // Reiniciar para el siguiente tablero si hubiera varios
            }
        }

[ \t\n] { /* Ignorar espacios y saltos de línea */ }

.       { /* Ignorar cualquier otro caracter */ }

%%

void evaluar_juego() {
    int combinaciones[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // Horizontales
        {0,3,6}, {1,4,7}, {2,5,8}, // Verticales
        {0,4,8}, {2,4,6}           // Diagonales
    };

    int ganador_x = 0;
    int ganador_o = 0;
    int espacios_vacios = 0;

    for(int i = 0; i < 9; i++) if(tablero[i] == '_') espacios_vacios++;

    for(int i = 0; i < 8; i++) {
        char a = tablero[combinaciones[i][0]];
        char b = tablero[combinaciones[i][1]];
        char c = tablero[combinaciones[i][2]];
        
        if (a != '_' && a == b && b == c) {
            if (a == 'X') ganador_x = 1;
            if (a == 'O') ganador_o = 1;
        }
    }

    // Imprimir resultado según la prioridad del juego
    if (ganador_x) printf(" -> gana X\n");
    else if (ganador_o) printf(" -> gana O\n");
    else if (espacios_vacios > 0) printf(" -> sin ganador\n");
    else printf(" -> empate\n");
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) return 1;
    }
    yylex();
    return 0;
}