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

    matrice G = NewMatrice(n,k);
    PrintMatrice(G);
    SetIdentity(G,G.rows);
    PrintMatrice(G);
    matrice H = NewMatrice(n,my_log_2(n)); //faire log2 de n
    PrintMatrice(H);

    /* int taille;
    int test = atoi(argv[3]);
    int* res = GetBinaryCode(test,&taille);
    for(int i=0;i<my_log_2(atoi(argv[3]));i++){
        printf("res[%d]=%d\n",i,res[i]);
    }*/

    SetControleMat(H);
    PrintMatrice(H);
    TransformControlMat(H);
    PrintMatrice(H);

    matrice P = GetPtrans(H);
    PrintMatrice(P);

    matrice Ptrans = Transpose(P);
    PrintMatrice(Ptrans);

    PrintMatrice(G);
    CompleteG(G,Ptrans);
    PrintMatrice(G);

    return EXIT_SUCCESS;
}