#include <stdio.h>
#include "matrice.h"

int main (int argc, char** argv){
    if(argc!=3){
        printf("Syntaxe : %s [ n ] [ mot à decoder ]\n",argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]); 
    int len_word = 0;
    for(int i=0;argv[2][i]!='\0';i++){
        len_word++;
    }
    matrice u = NewMatrice(len_word,1);
    for(int i=0;i<len_word;i++){
        char c = argv[2][i];
        if(c==48){
            u.data[i] = 0;
        }else if(c==49){
            u.data[i] = 1;
        }else{
            printf("ERREUR"),
            exit(EXIT_FAILURE);
        }
    }
    matrice H = NewMatrice(n,my_log_2(n));
    SetControleMat(H);
    H = Transpose(H);
    /*printf("H:\n");
    PrintMatrice(H);
    printf("u:\n");
    PrintMatrice(u);*/
    matrice Syndrome = ProduitMatriciel(u,H);
    printf("Syndrome : ");
    PrintMatrice(Syndrome);
    if(IsMatriceZero(Syndrome)){
        printf("Le mot codé est juste ou bien il y a trop dérreurs\n");
    }else{
        int pos = CheckPositionError(Syndrome,H);
        printf("Une erreur détécté à la position %d\n",pos);
        if(u.data[pos]==1){
            u.data[pos]=0;
        }else{
            u.data[pos]=1;
        }
    }
    printf("mot décodé :");
    PrintWord(u);
    printf("\n");
    return EXIT_SUCCESS;
}