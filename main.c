#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include <omp.h>

/**
 * Protótipo de funções
 */
void escolhaModo();
int modoInterativo();
int modoArquivo();
int geraAleatorio();
int *alocaVetor(int n);
void trocaElemento(int *v, int i, int j);
void inicializaVetor(int *v, int n);
void permuta(int *v, int n, int i, int cidadeInicial, int matriz[n][n], int *dMenor, int vetorDistancia[]);

/**
 * Função responsável pela escolha do modo de execução do programa
 * Entrada 1 = modo INTERATIVO
 * Entrada 2 = modo ARQUIVO
 * Outra = escolhaModo()
 */
void escolhaModo() {
    int opcaoModo = 0, erroI, erroA;
    while (opcaoModo == 0) {
        printf("Como deseja executar: \n1 - Interativo\n2 - Arquivo\n3 - Sair\nEntre com sua opção: ");
        scanf("%d", &opcaoModo);
        if (opcaoModo == 1) {
            erroI = modoInterativo();
        } else if (opcaoModo == 2) {
            erroA = modoArquivo();
        } else if (opcaoModo == 3) {
            break;
        } else {
            printf("Entre com uma opção válida!\n");
            opcaoModo = 0;
        }
    }

}

int modoInterativo() {
    clock_t Ticks[2];
    int menorDistancia = INT_MAX;
    int *v, n, i, j, mat1, mat2, mat3, soma, inicio;
    printf("Digite a matrícula 1: ");
    scanf("%d", &mat1);
    printf("Digite a matrícula 2: ");
    scanf("%d", &mat2);
    printf("Digite a matrícula 3: ");
    scanf("%d", &mat3);
    printf("Digite a quantidade de cidades: ");
    scanf("%d", &n);
    int matriz[n][n], vetorDistancia[n];
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j) {
                matriz[i][j] = geraAleatorio();
            } else {
                matriz[i][j] = 0;
            }
        }
    }
    soma = mat1 + mat2 + mat3;
    inicio = soma % n;
    printf("======================================\n");
    printf("Matricula 1: %d\nMatricula 2: %d\nMatricula 3: %d\n", mat1, mat2, mat3);
    printf("======================================\n");
    printf("======================================\n");
    printf("Qtd de cidades: %d\n", n);
    printf("======================================\n");
    printf("Cidade Inicial: %d\n", inicio);
    printf("======================================\n");
    v = alocaVetor(n);
    inicializaVetor(v, n);
    Ticks[0] = clock();
    permuta(v, n, 0, inicio, matriz, &menorDistancia, vetorDistancia);
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("======================================\n");
    printf("Matriz Distancia\n");
    printf("======================================\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("======================================\n");
    printf("A menor distância foi: %d\n", menorDistancia);
    printf("======================================\n");
    printf("Sequencia de cidade percorridas\n");
    for(i=0;i<n;i++){
        printf("%d ", vetorDistancia[i]);
    }
    printf("%d\n", inicio);
    printf("======================================\n");
    printf("Tempo de execução: %g ms\n", Tempo);
    printf("======================================\n");
    escolhaModo();
    return 0;
}

/**
 * Função responsável pela execução do modo de leitura de arquivo
 * @return int 0 caso erro ou 1 caso sucesso
 */
int modoArquivo() {
    clock_t Ticks[2];
    int menorDistancia = INT_MAX;
    char nomeArquivo[255];
    int mat[3], i, j, n;
    int *v, soma = 0, cidadeInicial = 0;
    FILE *arquivo = NULL;
    printf("Entre com o caminho e a extensão do arquivo: ");
    scanf(" %s", nomeArquivo);
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("%s nao existe.\nEntre com um caminho/arquivo válido!", nomeArquivo);
        modoArquivo();
        return 0;
    } else {
        for (i = 0; i < 3; i++) {
            fscanf(arquivo, "%d", &mat[i]);
            soma += mat[i];
        }
        fscanf(arquivo, "%d", &n);
        int matriz[n][n], vetorDistancia[n];
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (i == j) {
                    matriz[i][j] = 0;
                } else {
                    fscanf(arquivo, "%d", &matriz[i][j]);
                }
            }
        }
        cidadeInicial = soma % n;
        if (cidadeInicial == 0) cidadeInicial = 1;
        v = alocaVetor(n);
        inicializaVetor(v, n);
        printf("\n======================================\n");
        for (i = 0; i < 3; i++) {
            printf("Matricula %d: %d\n", i + 1, mat[i]);
        }
        printf("======================================\n");
        printf("======================================\n");
        printf("Qtd de cidades: %d\n", n);
        printf("======================================\n");
        printf("======================================\n");
        printf("Cidade Inicial: %d\n", cidadeInicial);
        printf("======================================\n");
        Ticks[0] = clock();
        permuta(v, n, 0, cidadeInicial, matriz, &menorDistancia, vetorDistancia);
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("======================================\n");
        printf("Matriz Distancia\n");
        printf("======================================\n");
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
        printf("======================================\n");
        printf("A menor distancia foi: %d\n", menorDistancia);
        printf("======================================\n");
        printf("Sequencia de cidades pecorridas\n");
        for (i = 0; i < n; i++) {
            printf("%d ", vetorDistancia[i]);
        }
        printf("%d\n", cidadeInicial);
        printf("======================================\n");
        printf("Tempo de execução: %g ms\n3", Tempo);
        printf("======================================\n");
        escolhaModo();
        return 0;
    }
}

/**
 * Função responśavel pela geração aleatória de números inteiros entre 0 e 100
 * @return int número aleatório entre 0 e 100
 */
int geraAleatorio() {
    return (0 + rand() % (100 + 1 - 0));
}

/**
 * Função repsonsável pela alocação dinâmica do vetor
 * @param n int tamanho do vetor
 * @return int ponteiro para o vetor alocado
 */
int *alocaVetor(int n) {
    int *v = (int *) (malloc(sizeof (int)*n));
    return v;
}

/**
 * Função responável pela troca do elemento do vetor durante a permutação
 * @param v int ponteiro para o vetor alocado
 * @param i int 1º elemento
 * @param j int 2º elemento
 */
void trocaElemento(int *v, int i, int j) {
    int aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

/**
 * Função responsável pela inicialização do vetor
 * @param v int ponteiro para o vetor alocado
 * @param n int tamanho do vetor alocado
 */
void inicializaVetor(int *v, int n) {
    int i;
    if (v != NULL) {
        for (i = 0; i < n; i++)
            v[i] = i + 1;
    } else {
        printf("Vetor Nulo!\n");
    }
}

/**
 * Função responsável pela permutação do vetor alocado anteriormente
 * @param v int ponteiro para o vetor alocado
 * @param n int tamanho do vetor alocado
 * @param i int posição para permutação
 * @param cidadeInicial int cidade de início (resultado das matrículas somadas mod n)
 * @param matriz int matriz gerada aleatoriamente anteriormente
 * @param dMenor int ponteiro para a medida de menor distância
 */
void permuta(int *v, int n, int i, int cidadeInicial, int matriz[n][n], int *dMenor, int vetorDistancia[]) {
    int menorD;
    int j;
    int soma = 0;
    if (i == n) {
        if (v[0] == cidadeInicial) {
            for (j = 0; j < n; j++) {
                printf(" %d ", v[j]);
            }
            printf(" %d ", cidadeInicial);
            for (j = 0; j < n - 1; j++) {
                soma += matriz[v[j]][v[j + 1]];
            }
            soma += matriz[v[n - 1]][v[0]];
            printf("- Distancia %d\n", soma);
            menorD = soma;
            if (*dMenor > menorD) {
                *dMenor = menorD;
                for (j = 0; j < n; j++) {
                    vetorDistancia[j] = v[j];
                }
            }
        }
    } else {
        for (j = i; j < n; j++) {
            trocaElemento(v, i, j);
            permuta(v, n, i + 1, cidadeInicial, matriz, dMenor, vetorDistancia);
            trocaElemento(v, i, j);
        }
    }
}

int main(void) {
    srand(time(NULL));
    int nthreads, tid;
    //Bifurca uma equipe de threads dando-lhes suas próprias cópias de variáveis ​​
    #pragma omp paralelo private (nthreads, tid)
    escolhaModo();
    return 0;
}
