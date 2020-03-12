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
    printf("Longuer du mot à coder : %d\n",len_word);

    matrice G = NewMatrice(n,k);
    PrintMatrice(G);
    SetIdentity(G,G.rows);
    PrintMatrice(G);
    matrice H = NewMatrice(n,my_log_2(n)); //faire log2 de n

    /* int taille;
    int test = atoi(argv[3]);
    int* res = GetBinaryCode(test,&taille);
    for(int i=0;i<my_log_2(atoi(argv[3]));i++){
        printf("res[%d]=%d\n",i,res[i]);
    }*/

    SetControleMat(H);
    //TransformControlMat(H);
    printf("Matrice de Controle H :\n");
    PrintMatrice(H);

    matrice P = GetPtrans(H);
    matrice Ptrans = Transpose(P);
    CompleteG(G,Ptrans);
    printf("Matrice Génératrice G :\n");
    PrintMatrice(G);

    matrice u = NewMatrice(len_word,1);
    int* u_binary = malloc(len_word*sizeof(int));
    int u_nb = atoi(argv[3]);
    int diviseur=1;
    for(int i=0;i<len_word-1;i++){
        diviseur*=10;
    }
    for(int i=0;i<len_word;i++){
        u_binary[i] = u_nb/diviseur;
        u_nb %= diviseur;
        diviseur /= 10;
    }
    for(int i=0;i<len_word;i++){
        u.data[i] = u_binary[i];
    }
    printf("Mot à coder u :\n");
    PrintMatrice(u);

    matrice v = ProduitMatriciel(u,G);
    printf("Mot encodé v :\n");
    PrintMatrice(v);

    return EXIT_SUCCESS;
}