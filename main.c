#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


FILE  *ListaDeAlunos;
FILE *ListaAuxiliar;
FILE *ListaOrdenadaAlunos;


char fieldContent[40];


void resetFile(char *file){
    //reseta o arquivo que ira receber a lista de alunos ordenada
    ListaDeAlunos = fopen(file,"w");
    fclose(ListaDeAlunos);
}


void writeOnFile(char*content ){
    ListaDeAlunos = fopen("listaOrdenadaDeAlunos.txt","a");
    fprintf(ListaDeAlunos,"%s\n",content);
    fclose(ListaDeAlunos);
}

int generateRandomInt(int numCap){
    int num;
    num = rand() % numCap + 1;

    return num;
}

float generateRandomFloat() {
    float max = 10.0;
    float num = ((float)rand()/(float)(RAND_MAX)) * max;

    return num;
}

char *readSpecificLineInFile(int line, char* fileName, char *lineContent){
    char linha[90];
    ListaDeAlunos = fopen(fileName,"r");

    strcpy(lineContent, "Minha string de exemplo");

    for (int i = 0; i < line; ++i) {
        fscanf(ListaDeAlunos, "%s", linha);
        strcpy(lineContent, linha);
    }

    fclose(ListaDeAlunos);
    return lineContent;
}

char *generateStudent(int numberOfStudents){
    int semestre[8]={1,2,3,4,5,6,7,8};
    char materias[4][30] = {"","portugues", "matematica", "geografia"};
    char periodo[3] = {' ','M','N'};
    char sala[3] = {' ','A','B'};
    ListaAuxiliar = fopen("dadosAlunos.txt","a");
    char *lineContent = malloc(100 * sizeof(char));

    for (int i = 0; i < numberOfStudents; ++i) {
        fprintf(ListaAuxiliar,"%c,%c,%s,%s,%.2f\n",
                sala[generateRandomInt(2)],
                periodo[generateRandomInt(2)],
                readSpecificLineInFile(generateRandomInt(40),"nomesAlunos.txt", lineContent),
                materias[generateRandomInt(3)],
                generateRandomFloat());
    }
    free(lineContent);
    fclose(ListaAuxiliar);
}

char * selectField(int field, char *data){
    //coloca o valor lido depois da N virgula em fieldContent\
    // colocar 0 no field da pau
    //para acessar periodo field devera receber 1
    // para acessar nome field devera receber 2
    // para acessar materia field devera receber 3
    // para acessar media field devera receber 4
    char userData[90];

    strcpy(userData,data);
    char *auxFieldContent  = malloc(100 * sizeof(char));


    char * token = strtok(userData, ",");
    int i = 0;

    while( i!=field ) {
        token = strtok(NULL, ",");
        strcpy(auxFieldContent,token);
        i++;
    }

    return auxFieldContent;
}

int main() {

    srand(20000000*time(NULL));

    int option = 0;

    while (option!=4){
        printf("Gerar alunos aleatorios -> 1\n");
        printf("Ordenar por nota via BubbleSort -> 2\n");
        printf("Ordenar por nota via CleitonSort -> 3\n");
        printf("Finalizar programa -> 4\n");

        printf("Qual opcao deseja acessar?\n");
        scanf("%d",&option);
        if (option==1) {
            int nOfStudents=0;
            printf("Quantos alunos deseja gerar?: \n");
            scanf("%d",&nOfStudents);
            generateStudent(nOfStudents);
        }
        if (option==2){
            printf("Opcao 2 yaaaay\n");

        }
        if (option==3){
            printf("Opcao 3 yaaaay\n");

        }

    }



    printf("Obrigado por utilizar nosso programa :)\n");


    return 0;
}
