#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *ListaDeAlunos;
FILE *ListaAuxiliar;
FILE *ListaOrdenadaAlunos;
FILE *File;

char fieldContent[40];

void resetFile(char *file) {
    // reseta o arquivo que ira receber a lista de alunos ordenada
    ListaDeAlunos = fopen(file, "w");
    fclose(ListaDeAlunos);
}

void writeOnFile(char *content) {
    ListaDeAlunos = fopen("listaOrdenadaDeAlunos.txt", "a");
    fprintf(ListaDeAlunos, "%s\n", content);
    fclose(ListaDeAlunos);
}

int generateRandomInt(int numCap) {
    int num;
    num = rand() % numCap + 1;

    return num;
}

float generateRandomFloat() {
    float max = 10.0;
    float num = ((float)rand() / (float)(RAND_MAX)) * max;

    return num;
}

char *readSpecificLineInFile(int line, char *fileName, char *lineContent) {
    char linha[90];
    ListaDeAlunos = fopen(fileName, "r");

    strcpy(lineContent, "Minha string de exemplo");

    for (int i = 0; i < line; ++i) {
        fscanf(ListaDeAlunos, "%s", linha);
        strcpy(lineContent, linha);
    }

    fclose(ListaDeAlunos);
    return lineContent;
}

void generateStudent(int numberOfStudents) {
    int semestre[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    char materias[4][30] = {"", "portugues", "matematica", "geografia"};
    char periodo[3] = {' ', 'M', 'N'};
    char sala[3] = {' ', 'A', 'B'};
    ListaAuxiliar = fopen("dadosAlunos.txt", "a");
    char *lineContent = malloc(100 * sizeof(char));

    for (int i = 0; i < numberOfStudents; ++i) {
        fprintf(ListaAuxiliar, "%c,%c,%s,%s,%.2f\n", sala[generateRandomInt(2)],
                periodo[generateRandomInt(2)],
                readSpecificLineInFile(generateRandomInt(40), "nomesAlunos.txt",
                                       lineContent),
                materias[generateRandomInt(3)], generateRandomFloat());
    }
    free(lineContent);
    fclose(ListaAuxiliar);
}

void selectField(int field, char *data, char auxFieldContent[]) {
    //coloca o valor lido depois da N virgula em fieldContent\
    // colocar 0 no field da pau
    // para acessar periodo field devera receber 1
    //  para acessar nome field devera receber 2
    //  para acessar materia field devera receber 3
    //  para acessar media field devera receber 4
    char userData[90];

    strcpy(userData, data);

    char *token = strtok(userData, ",");
    int i = 0;

    while (i != field) {
        token = strtok(NULL, ",");
        strcpy(auxFieldContent, token);
        i++;
    }
}

int checkFileSize() {
    char linha[90];
    int index = 0;
    File = fopen("dadosAlunos.txt", "r");
    while (fscanf(File, "%s", linha) != EOF) {
        index++;
    }
    fclose(File);

    return index;
}

void transferToMemory(char fileName[], char **vector) {
    File = fopen(fileName, "r");
    char linha[40];
    int i = 0;
    while(fscanf(File, "%s", linha) != EOF) {
        strcpy(vector[i], linha);
        i++;
    }
    fclose(File);
}


void transferToFile(char fileName[], char **vector, int size) {
    File = fopen(fileName, "w");
    for(int i = 0; i < size; i++) {
        fprintf(File, "%s\n", vector[i]);
    }
}


int bubleSort(char **vector, int size) {
    int contador = 0;
    char aux[40];
    char v1[100], v2[100];

    for (int i = 1; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            contador++;
            selectField(4, vector[j], v1);
            selectField(4, vector[j + 1], v2);
            if (strcmp(v1, v2) > 0) {
                strcpy(aux, vector[j]);
                strcpy(vector[j], vector[j + 1]);
                strcpy(vector[j + 1], aux);
            }
        }
    }
    return contador;
}
int partition(char **array, int low, int high) {
    // select the rightmost element as pivot
    char pivot[40];
    char aux[40];
    char v1[100], v2[100];
    strcpy(pivot, array[high]);

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        selectField(4, array[j], v1);
        selectField(4, pivot, v2);
        if (strcmp(v1, v2) <= 0) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            strcpy(aux, array[j]);
            strcpy(array[j], array[i]);
            strcpy(array[i], aux);
        }
    }
    // swap the pivot element with the greater element at i
    strcpy(aux, array[i + 1]);
    strcpy(array[i + 1], array[high]);
    strcpy(array[high], aux);

    // return the partition point
    return (i + 1);
}



int quickSort(char **array, int low, int high) {
    int contador=1;
    if (low < high) {
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        contador += quickSort(array, low, pi - 1);
        // recursive call on the right of pivot
        contador += quickSort(array, pi + 1, high);
    }
    return contador;
}



int main() {
    // Declaraçao de vals scop main
    srand(20000000 * time(NULL));
    int option = 0;
    char menu[] = "[1] - Gerar alunos aleatorios.\n[2] - Ordenar por nota via "
                  "BubbleSort.\n[3] - Ordenar por nota via CleitonSort.\n[4] - "
                  "Finalizar o programa.\n";

    while (option != 4) {
        printf("%s", menu);
        printf("Qual opcao deseja acessar?\n");
        scanf("%d", &option);

        if (option == 1) {
            int nOfStudents = 0;
            printf("Quantos alunos deseja gerar?: \n");
            scanf("%d", &nOfStudents);
            generateStudent(nOfStudents);
        }
        else if (option == 2) {
            //inicia a contagem do tempo
            clock_t t;
            t = clock();

            // cria um vetor do tamanho do arquivo
            int rows = checkFileSize();
            char **matrix = (char **)malloc(rows * sizeof(char *));
            for(int i=0; i<rows; i++) {
                matrix[i] = (char *)malloc(40 * sizeof(char));
            }
            // transfere o conteudo do arquivo para o vetor
            transferToMemory("dadosAlunos.txt", matrix);
            // ordena o vetor e armazena o numero de iteracoes
            int iterations = bubleSort(matrix, rows);


            // armazena em arquivo
            transferToFile("ListaOrdenada" , matrix, rows);
            //finaliza o tempo
            t = clock() - t;

            // saida
            printf("Algoritmo: Bubble Sort\n");
            printf("Tamanho Entrada: %d\n", checkFileSize());
            printf("Tempo de execução: %f\n", ((float)t/CLOCKS_PER_SEC)); //FALTA FAZER
            printf("Comparações (passos): %d\n", iterations);
            printf("\n");

            // Libera a matrix
            for(int i=0; i<rows; i++) {
                free(matrix[i]);
            }
            free(matrix);

        }
        else if (option == 3) {
            //inicia a contagem do tempo
            clock_t t;
            t = clock();

            // cria um vetor do tamanho do arquivo
            int rows = checkFileSize();
            char **matrix = (char **)malloc(rows * sizeof(char *));
            for(int i=0; i<rows; i++) {
                matrix[i] = (char *)malloc(40 * sizeof(char));
            }
            // transfere o conteudo do arquivo para o vetor
            transferToMemory("dadosAlunos.txt", matrix);
            // ordena o vetor e armazena o numero de iteracoes
            int iterations = quickSort(matrix, 0, rows-1);

            // armazena em arquivo
            transferToFile("ListaOrdenada" , matrix, rows);
            //finaliza o tempo
            t = clock() - t;

            // saida
            printf("Algoritmo: Quick Sort\n");
            printf("Tamanho Entrada: %d\n", rows);
            printf("Tempo de execução: %f\n", ((float)t/CLOCKS_PER_SEC));
            printf("Comparações (passos): %d\n", iterations);
            printf("\n");

            // Libera a matrix
            for(int i=0; i<rows; i++) {
                free(matrix[i]);
            }
            free(matrix);
        }
    }

    printf("Obrigado por utilizar nosso programa :)\n");

    return 0;
}
