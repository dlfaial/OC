#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxim 1
#define Minim 0
#define MaiorIgual 1
#define MenorIgual -1
#define Igual 0

FILE* pl;
int nVariaveis, nRestricoes, tipoProblema, nFolga, nArtificiais, nVarTotal;
int* sinais;
int* base;
double* variaveis;
double** restricoes;
double** matriz;
double* funcObj;
double* b;
int* base;

void InverteB(){
    int i, j;
    for(i=0; i<nRestricoes; i++){
        if(b[i]<0){
            for(j=0; j<nVariaveis; j++){
                restricoes[i][j] = restricoes[i][j] * (-1);
            }
            b[i] = b[i] * (-1);
        }
    }
}

void PreencheRestricoes(){
    int i, j;

    for(i=0; i<nRestricoes; i++){
        for(j=0; j<nVariaveis; j++){
            matriz[i][j] = restricoes[i][j];
        }
    }
}

void PreencheFolgaArtificiais(){
    int i, j;
    int k=0;
    int coluna = nVariaveis;
    int linha = 0;

    for(i=0; i<nRestricoes; i++){
        if(sinais[i] == MenorIgual){
            matriz[linha][coluna] = 1;
            base[k] = coluna;
            linha++;
            coluna++;
            k++;
        }
        else if(sinais[i] == Igual){
            matriz[linha][coluna] = 1;
            base[k] = coluna;
            linha++;
            coluna++;
            k++;
        }
        else{
            matriz[linha][coluna] = -1;
            coluna++;
            matriz[linha][coluna] = 1;
            base[k] = coluna;
            linha++;
            coluna++;
            k++;
        }

    }
}

void PreencheB(){
    int i;

    for(i=0; i<nRestricoes; i++){
        matriz[i][nVarTotal] = b[i];
    }
}

void PreencheFO(){
    int j;

    for(j=0; j<nVarTotal; j++){
        matriz[nRestricoes][j] = funcObj[j];
    }
}

void ImprimeMatriz(){
    int i, j;

    for(i=0; i<=nRestricoes; i++){
        for(j=0; j<=nVarTotal; j++){
            printf("%5.2f ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

}

void PreencheM(){
    int i,j;
        for (i = 0; i<nRestricoes; i++){
            for (j = 0; j<nVariaveis; j++){
                matriz[i][j] = 666;
            }
        }
}

int main()
{
    // Arquivo
    char nomeArq[30];
    //printf("Digite o nome do arquivo:  ");
    //scanf(" %[^\n]", nomeArq);
    pl = fopen("problema1.txt", "r");
    fscanf(pl, "%d %d %d", &nRestricoes, &nVariaveis, &tipoProblema);

    funcObj = (double*) malloc(nVariaveis*sizeof(double));

    int i, j;
    for(i=0; i<nVariaveis; i++){
        fscanf(pl, "%lf", &funcObj[i]);
    }

    b = (double*) malloc(nRestricoes*sizeof(double));

    restricoes = (double**) malloc(nRestricoes*sizeof(double*));
    for(i=0; i<nRestricoes; i++){
        restricoes[i] = (double*) malloc(nVariaveis*sizeof(double));
    }
    nFolga = nArtificiais = 0;

    // sinais armazena o sinal de cada restricao
    sinais = (int*) malloc(nRestricoes*sizeof(int));

    for(i=0; i<nRestricoes; i++){
        for(j=0; j<nVariaveis; j++){
            fscanf(pl, "%lf", &restricoes[i][j]);
        }
        char sinal1, sinal2;
        fscanf(pl, " %c%c", &sinal1, &sinal2);

        if(sinal1 == '>'){
            sinais[i] = MaiorIgual;
        }
        else if(sinal1 == '<'){
            sinais[i] = MenorIgual;
        }
        else{
            sinais[i] = Igual;
        }

        fscanf(pl, "%lf", &b[i]);
    }

    nVarTotal = nVariaveis;

    // Contando colunas
    for(i=0; i<nRestricoes; i++){
        if(sinais[i]==MaiorIgual){
            nFolga++;
            nArtificiais++;
            nVarTotal+=2;
        }
        else if(sinais[i]==MenorIgual){
            nFolga++;
            nVarTotal++;
        }
        else{
            nArtificiais++;
            nVarTotal++;
        }
    }

    //Criando a matriz com todas colunas
    matriz = (double**) malloc((nRestricoes+1)*sizeof(double*));
    for(i=0; i<nRestricoes+1; i++){
        matriz[i]= (double*) malloc((nVarTotal+1)*sizeof(double));
    }

    //Inicializando
    for(i=0; i<=nRestricoes; i++){
        for(j=0; j<=nVarTotal; j++){
            matriz[i][j]=0;
        }
    }


    //Alocando base
    base = (int*) malloc(nRestricoes*sizeof(int));

    InverteB();
    PreencheRestricoes();
    PreencheFolgaArtificiais();
    PreencheB();
    PreencheFO();

    ImprimeMatriz();


    return 0;
}
