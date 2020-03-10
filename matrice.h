#include <stdlib.h>
#include <stdio.h>

typedef struct matrice{
    int* data;  //    1 2 3
    int rows;   //    4 5 6  -> data = [ 1, 2, 3, 4, 5, 6, 7, 8, 9] : rows per rows
    int cols;   //    7 8 9 
}matrice;


int my_pow_2(int a){
    if(a<0){
        return -1;
    }
    if(a==0){
        return 1;
    }
    int b = 1;
    return b << a;
}

int my_log_2(int a){
    int i=0;
    int pow2 = my_pow_2(0);
    while(a>=pow2){
        i++;
        pow2 = my_pow_2(i);
    }
    return i;
}


matrice NewMatrice(int cols, int rows){
    matrice m;
    m.cols = cols;
    m.rows = rows;
    m.data = (int*)malloc(cols*rows*sizeof(int));
    return m;
}

void PrintMatrice(matrice m){
    for(int i=0;i<(m.cols*m.rows);i++){
        if((i%m.cols==0) && (i!=0)){
            printf("\n");
        }
        printf("%d",m.data[i]);
    }
    printf("\n\n");
}

void SetIdentity(matrice m, int dim){
    for(int i=0;i<dim;i++){
        m.data[i*m.cols + i] = 1;
    }
}

int* GetBinaryCode(int a, int* tablg){
    int taille = my_log_2(a);
    int * tab = (int*)malloc(taille*sizeof(int));
    for(int i=0;i<taille;i++){
        tab[i] = a%2;
        a /= 2;
    }
    *tablg = taille;
    return tab;
}

void WriteCol(int* tab, int taille, int taille_max, int col, matrice m){
    for(int i=0;i<taille_max;i++){
        if(i<taille){
            m.data[col+m.cols*(taille_max-1-i)] = tab[i];
        }else{
            m.data[col+m.cols*(taille_max-1-i)] = 0;
        }
    }
}

void SetControleMat(matrice h){
    int taille_max = my_log_2(h.cols);
    int taille;
    for(int i=1;i<=h.cols;i++){
        int* tab = GetBinaryCode(i,&taille);
        WriteCol(tab,taille,taille_max,i-1,h);
    }
}