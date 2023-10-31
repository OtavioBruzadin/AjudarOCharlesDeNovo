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
    srand(2000000*time(NULL));
    num = rand() % numCap + 1;

    return num;
}

float generateRandomFloat() {

    srand(20000000*time(NULL));
    float max = 10.0;
    float num = ((float)rand()/(float)(RAND_MAX)) * max;
    return num;
}

char *readSpecificLineInFile(int line){

    char linha[90];
    char *lineContent = malloc(100 * sizeof(char));
    ListaDeAlunos = fopen("listaDeAlunos.txt","r");

    strcpy(lineContent, "Minha string de exemplo");

    for (int i = 0; i <= line; ++i) {
        fscanf(ListaDeAlunos, "%s", linha);\
            strcpy(lineContent, linha);

    }
    return lineContent;
}

char *generateStudent(int numberOfStudents){
    int semestre[]={1,2,3,4,5,6,7,8};
    char *materias[] = {"","portugues", "matematica", "geografia"};
    char periodo[] = {'M','N'};
    char sala[] = {'A','B'};

    for (int i = 0; i < numberOfStudents; ++i) {
        ListaAuxiliar = fopen("listaOrdenadaDeAlunos.txt","a");

        fprintf(ListaAuxiliar,"%c,%c,%s,%s,%.2f\n",
                sala[generateRandomInt(2)],
                periodo[generateRandomInt(2)],
                readSpecificLineInFile(generateRandomInt(40)),
                materias[generateRandomInt(3)],
                generateRandomFloat());
        Sleep(1000);
    }
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
    for (int i = 0; i < 20; ++i) {
        generateStudent(10);
        printf("\nterminou a %d vez",i);

    }

    return 0;
}
