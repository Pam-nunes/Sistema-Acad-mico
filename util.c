#include <stdio.h>
#include <stdlib.h>

void obter_texto(char **texto) {
    char caractere;
    int tamanho_texto = 0;
    *texto = NULL; 

    while ((caractere = getchar()) != '\n') {
        char *temp = realloc(*texto, (tamanho_texto + 1) * sizeof(char));
        if (temp == NULL) {
            printf("\nErro de alocacao de memoria.\n");
            free(*texto); 
            exit(1);
        }
        *texto = temp;
        (*texto)[tamanho_texto] = caractere;
        tamanho_texto++;
    }

    
    char *temp = realloc(*texto, (tamanho_texto + 1) * sizeof(char));
    if (temp == NULL) {
        printf("\nErro de alocacao de memoria.\n");
        free(*texto);
        exit(1);
    }
    *texto = temp;
    (*texto)[tamanho_texto] = '\0';
}
