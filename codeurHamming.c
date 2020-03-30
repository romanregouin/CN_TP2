#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"

int main(int argc, char** argv){
    if(argc!=4){
        printf("Syntaxe : %s [ n ] [ k ] [ mot a coder ]\n",argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]); 
    if((n+1)!=my_pow_2(n-k)){
        printf("n+1 must be equal to 2^(n-k). Currently we have %d != %d\n",n+1,my_pow_2(n-k));
        return EXIT_FAILURE;
    }

    int len_word = 0;
    for(int i=0;argv[3][i]!='\0';i++){
        len_word++;
    }
    //printf("Longuer du mot à coder : %d\n",len_word);

    matrice G = NewMatrice(n,k);
    //PrintMatrice(G);
    SetIdentity(G,G.rows);
    //PrintMatrice(G);
    matrice H = NewMatrice(n,my_log_2(n)); //faire log2 de n

    /* int taille;
    int test = atoi(argv[3]);
    int* res = GetBinaryCode(test,&taille);
    for(int i=0;i<my_log_2(atoi(argv[3]));i++){
        printf("res[%d]=%d\n",i,res[i]);
    }*/

    SetControleMat(H);
    //TransformControlMat(H);
    //printf("Matrice de Controle H :\n");
    //PrintMatrice(H);

    /*matrice P = GetPtrans(H);
    matrice Ptrans = Transpose(P);
    CompleteG(G,Ptrans);
    printf("Matrice Génératrice G :\n");
    PrintMatrice(G);*/

    matrice u = NewMatrice(len_word,1);
    for(int i=0;i<len_word;i++){
        char c = argv[3][i];
        if(c==48){
            u.data[i] = 0;
        }else if(c==49){
            u.data[i] = 1;
        }else{
            printf("ERREUR"),
            exit(EXIT_FAILURE);
        }
    }
    printf("Mot à coder u :\n");
    PrintMatrice(u);

    matrice tmp = CalculBitsParite(H,u);
    printf("Mot codé :\n");
    PrintMatrice(tmp);

    /*matrice v = ProduitMatriciel(u,G);
    printf("Mot encodé v :\n");
    PrintMatrice(v);*/

    return EXIT_SUCCESS;
}