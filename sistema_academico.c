#include <stdio.h>
#include <stdlib.h>

typedef struct aluno
{
    int matricula;
    char *nome;
    char *telefone;
} t_aluno;

typedef struct disciplina
{
    int codigo;
    char *nome;
    t_aluno *alunos;
    int quantidade_alunos;
} t_disciplina;

typedef struct turma
{
    int numero;
    t_disciplina *disciplinas;
    int quantidade_disciplinas;
} t_turma;

typedef struct curso
{
    t_turma *turmas;
    int quantidade_turmas;
} t_curso;


void inserir_turma(t_curso *curso)
{
    listar_turmas(curso);
    int numTurma = 0;

    printf("\nInforme o numero da nova turma: ");
    scanf("%d", &numTurma);

    if (existe_turma(curso, numTurma) == 1)
    {
        printf("\nA turma ja existe! \nVoce nao pode insirir turmas iguais.\n");
        return;
    }
    else
    {
        curso->quantidade_turmas++;
        curso->turmas = realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));

        if (curso->turmas == NULL)
        {
            printf("\nErro de alocacao de memoria.\n");
            exit(1);
        }

        t_turma *turma_x = &curso->turmas[curso->quantidade_turmas - 1];

        turma_x->numero = numTurma;

        turma_x->disciplinas = NULL;
        turma_x->quantidade_disciplinas = 0;
    }
    printf("\nTurma nova inserida com sucesso...\n");
}

void inserir_disciplina(t_turma *turma)
{
    listar_disciplinas(turma);
    int numDisciplina = 0;

    printf("\nInforme o codigo da nova disciplina: ");
    scanf("%d", &numDisciplina);

    if (existe_disciplina(turma, numDisciplina))
    {
        printf("\nA disciplina ja existe!\nVoce nao pode insirir disciplinas iguais.\n");
        return;
    }
    else
    {
        turma->quantidade_disciplinas++;
        turma->disciplinas = realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));
        if (turma->disciplinas == NULL)
        {
            printf("\nErro de alocacao de memoria.\n");
            exit(1);
        }
        t_disciplina *disciplina_x = &turma->disciplinas[turma->quantidade_disciplinas - 1];
        getchar();
        printf("Informe o nome da nova disciplina: ");
        obter_texto(&disciplina_x->nome);
        disciplina_x->codigo = numDisciplina;
        disciplina_x->alunos = NULL;
        disciplina_x->quantidade_alunos = 0;
        printf("\nDisciplina inserida com sucesso...\n");
        listar_disciplinas(turma);
        
    }
}

void inserir_aluno(t_disciplina *disciplina)
{
    listar_alunos(disciplina);
    int numAluno = 0;

    printf("\nInforme a matricula do novo aluno: ");
    scanf("%d", &numAluno);

    while (getchar() != '\n');
    
    if (existe_aluno(disciplina, numAluno))
    {
        printf("\nO aluno ja existe!\nVoce nao pode insirir alunos iguais.\n");
        return;
    }
    else
    {
        disciplina->quantidade_alunos++;
        disciplina->alunos = realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
        if (disciplina->alunos == NULL)
        {
            printf("\nErro de alocacao de memoria.\n");
            exit(1);
        }
        t_aluno *aluno_x = &disciplina->alunos[disciplina->quantidade_alunos - 1];
        
        printf("Informe o nome do novo aluno: ");
        obter_texto(&aluno_x->nome);
        

        aluno_x->matricula = numAluno;

        printf("Informe o telefone do novo aluno: ");
        
        obter_texto(&aluno_x->telefone);
        

        
        printf("\nAluno cadastrado com sucesso...\n");
    }
}

void remover_turma(t_curso *curso)
{
    listar_turmas(curso);
    int numero;
    printf("\nNumero da turma a ser removida: ");
    scanf("%d", &numero);

    for (int i = 0; i < curso->quantidade_turmas; i++)
    {
        if (curso->turmas[i].numero == numero)
        {
            liberar_memoria_turma(&curso->turmas[i]);

            for (int j = i; j < curso->quantidade_turmas - 1; j++)
            {
                curso->turmas[j] = curso->turmas[j + 1];
            }

            curso->quantidade_turmas--;
            curso->turmas = realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));
            printf("\nTurma removida!\n");
            return;
        }
    }
    printf("\nTurma nao encontrada.\n");
}

void remover_disciplina(t_turma *turma)
{
    listar_disciplinas(turma);
    int codigo;
    printf("\nCodigo da disciplina a ser removida: ");
    scanf("%d", &codigo);

    for (int i = 0; i < turma->quantidade_disciplinas; i++)
    {
        if (turma->disciplinas[i].codigo == codigo)
        {
            liberar_memoria_disciplina(&turma->disciplinas[i]);

            for (int j = i; j < turma->quantidade_disciplinas - 1; j++)
            {
                turma->disciplinas[j] = turma->disciplinas[j + 1];
            }

            turma->quantidade_disciplinas--;
            turma->disciplinas = realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));
            printf("\nDisciplina removida!\n");
            return;
        }
    }
    printf("\nDisciplina nao encontrada.\n");
}

void remover_aluno(t_disciplina *disciplina)
{
    listar_alunos(disciplina);
    int matricula;
    printf("\nMatricula do aluno a ser removido: ");
    scanf("%d", &matricula);

    for (int i = 0; i < disciplina->quantidade_alunos; i++)
    {
        if (disciplina->alunos[i].matricula == matricula)
        {
            liberar_memoria_aluno(&disciplina->alunos[i]);

            for (int j = i; j < disciplina->quantidade_alunos - 1; j++)
            {
                disciplina->alunos[j] = disciplina->alunos[j + 1];
            }

            disciplina->quantidade_alunos--;
            disciplina->alunos = realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
            printf("\nAluno removido!\n");
            return;
        }
    }
    printf("\nAluno nao encontrado.\n");
}


void listar_turmas(t_curso *curso)
{
    if (curso->quantidade_turmas == 0)
    {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    for (int i = 0; i < curso->quantidade_turmas; i++)
    {
        printf("Turma numero: %d\n", curso->turmas[i].numero);
    }
}

void listar_disciplinas(t_turma *turma)
{
    if (turma->quantidade_disciplinas == 0)
    {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    for (int i = 0; i < turma->quantidade_disciplinas; i++)
    {
        printf("Codigo da disciplina: %d, Nome: %s\n", turma->disciplinas[i].codigo, turma->disciplinas[i].nome);
    }
}

void listar_alunos(t_disciplina *disciplina)
{
    if (disciplina->quantidade_alunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    for (int i = 0; i < disciplina->quantidade_alunos; i++)
    {
        printf("Matricula: %d, Nome: %s, Telefone: %s\n", disciplina->alunos[i].matricula, disciplina->alunos[i].nome, disciplina->alunos[i].telefone);
    }
}

t_turma *obter_turma(t_curso *curso)
{

    listar_turmas(curso);
    int numero;
    printf("\nDigite o numero da turma: ");
    scanf("%d", &numero);

    for (int i = 0; i < curso->quantidade_turmas; i++)
    {
        if (curso->turmas[i].numero == numero)
        {
            return &curso->turmas[i];
        }
    }
    printf("\nTurma nao encontrada.\n");
    return NULL;
}

t_disciplina *obter_disciplina(t_turma *turma)
{
    listar_disciplinas(turma);
    int codigo;
    printf("\nDigite codigo da disciplina: ");
    scanf("%d", &codigo);

    for (int i = 0; i < turma->quantidade_disciplinas; i++)
    {
        if (turma->disciplinas[i].codigo == codigo)
        {
            return &turma->disciplinas[i];
        }
    }
    printf("\nDisciplina nao encontrada.\n");
    return NULL;
}

t_aluno *obter_aluno(t_disciplina *disciplina)
{
    int matricula;
    printf("\nDigite a matricula do aluno: ");
    scanf("%d", &matricula);

    for (int i = 0; i < disciplina->quantidade_alunos; i++)
    {
        if (disciplina->alunos[i].matricula == matricula)
        {
            return &disciplina->alunos[i];
        }
    }
    printf("\nAluno nao encontrado.\n");
    return NULL;
}

void liberar_memoria_curso(t_curso *curso)
{
    for (int i = 0; i < curso->quantidade_turmas; i++)
    {
        liberar_memoria_turma(&curso->turmas[i]);
    }
    free(curso->turmas);
    curso->turmas = NULL;
    curso->quantidade_turmas = 0;
}

void liberar_memoria_turma(t_turma *turma)
{
    for (int i = 0; i < turma->quantidade_disciplinas; i++)
    {
        liberar_memoria_disciplina(&turma->disciplinas[i]);
    }
    free(turma->disciplinas);
    turma->disciplinas = NULL;
    turma->quantidade_disciplinas = 0;
}

void liberar_memoria_disciplina(t_disciplina *disciplina)
{
    for (int i = 0; i < disciplina->quantidade_alunos; i++)
    {
        liberar_memoria_aluno(&disciplina->alunos[i]);
    }
    free(disciplina->alunos);
    disciplina->alunos = NULL;
    disciplina->nome = NULL;
    disciplina->quantidade_alunos = 0;
}

void liberar_memoria_aluno(t_aluno *aluno)
{
    free(aluno->nome);
    free(aluno->telefone); 
}

int existe_turma(t_curso *curso, int numero)
{
    for (int i = 0; i < curso->quantidade_turmas; i++)
    {
        if (curso->turmas[i].numero == numero)
        {
            return 1; 
        }
    }
    return 0;
}

int existe_disciplina(t_turma *turma, int codigo)
{
    for (int i = 0; i < turma->quantidade_disciplinas; i++)
    {
        if (turma->disciplinas[i].codigo == codigo)
        {
            return 1; 
        }
    }
    return 0; 
}

int existe_aluno(t_disciplina *disciplina, int matricula)
{
    for (int i = 0; i < disciplina->quantidade_alunos; i++)
    {
        if (disciplina->alunos[i].matricula == matricula)
        {
            return 1; 
        }
    }
    return 0; 
}
