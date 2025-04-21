#include <stdio.h>
#include <stdlib.h>
#include "sistema_academico.h"

struct aluno {
	int matricula;
	char* nome;	
	long int telefone;
};
typedef struct aluno t_aluno;

struct disciplina {
	int codigo;
	char* nome;
	t_aluno* alunos;
	int quantidade_alunos;
};
typedef struct disciplina t_disciplina;

struct turma {
	int numero;
	t_disciplina* disciplinas;
	int quantidade_disciplinas;
};
typedef struct turma t_turma;

struct curso {
	t_turma* turmas;
	int quantidade_turmas;
};
typedef struct curso t_curso;


void exibir_menu(void)
{
    printf("\n\n---SISTEMA ACADEMICO---\n");
    printf(" 1- Inserir turmas\n");
    printf(" 2- Inserir disciplinas\n");
    printf(" 3- Inserir alunos\n");
    printf(" 4- Remover uma determinada turma\n");
    printf(" 5- Remover uma determinada disciplina\n");
    printf(" 6- Remover um determinado aluno\n");
    printf(" 7- Listar todas as turmas\n");
    printf(" 8- Listar todas as disciplinas\n");
    printf(" 9- Listar todos os alunos\n");
    printf(" 0- Sair do sistema\n");
}

int obter_opcao_menu(void)
{
    int opcao;
    printf("Escolha a opcao que deseja: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

void processar_opcao_menu(int opcao, t_curso *curso)
{
    switch (opcao)
    {
    case 1:
        inserir_turma(curso);
        break;
    case 2:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
            inserir_disciplina(turma);
        break;
    }
    case 3:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
        {
            t_disciplina *disciplina = obter_disciplina(turma);
            if (disciplina)
                inserir_aluno(disciplina);
        }
        break;
    }
    case 4:
        remover_turma(curso);
        break;
    case 5:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
            remover_disciplina(turma);
        break;
    }
    case 6:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
        {
            t_disciplina *disciplina = obter_disciplina(turma);
            if (disciplina)
                remover_aluno(disciplina);
        }
        break;
    }
    case 7:
        listar_turmas(curso);
        break;
    case 8:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
            listar_disciplinas(turma);
        break;
    }
    case 9:
    {
        t_turma *turma = obter_turma(curso);
        if (turma)
        {
            t_disciplina *disciplina = obter_disciplina(turma);
            if (disciplina)
                listar_alunos(disciplina);
        }
        break;
    }
    case 0:
        printf("\nO sistema foi encerrado.\n\nSaindo...\n");
        break;
    default:
        printf("\nOpcao invalida. \n Digite a opcao correta.\n\n");
    }
}
