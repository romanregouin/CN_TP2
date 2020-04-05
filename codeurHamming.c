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

    matrice H = NewMatrice(n,my_log_2(n));

    SetControleMat(H);

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

    return EXIT_SUCCESS;
}