#include "sistema_academico.h"
#include "principal.c"
#include "util.c"

void salvar_turmas(t_curso *curso) {
    FILE *arquivo = fopen("turmas.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de turmas.\n");
        return;
    }

    
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        fprintf(arquivo, "%d\n", curso->turmas[i].numero);
        salvar_disciplinas(&curso->turmas[i]);
    }

    fclose(arquivo);
}


void salvar_disciplinas(t_turma *turma) {
    FILE *arquivo = fopen("disciplinas.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de disciplinas.\n");
        return;
    }

    
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        fprintf(arquivo, "%d;%s\n", turma->disciplinas[i].codigo, turma->disciplinas[i].nome);
        salvar_alunos(&turma->disciplinas[i]);
    }

    fclose(arquivo);
}


void salvar_alunos(t_disciplina *disciplina) {
    FILE *arquivo = fopen("alunos.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de alunos.\n");
        return;
    }
