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

void PrintBinary(int* binary, int taille){
    for(int i=0;i<taille;i++){
        printf("%d",binary[taille-1-i]);
    }
    printf("\n");
}

//si on a=8 return [0,0,0,1] et 4 dans tablg
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

//permure la col1 avec la colone 2
void Permutation(matrice m, int col1, int col2){
    int save = 0;
    for(int i=0;i<m.rows;i++){
        save = m.data[col1+i*m.cols];
        m.data[col1+i*m.cols] = m.data[col2+i*m.cols];
        m.data[col2+i*m.cols] = save;
    }
}

int FindColOfBinary(matrice m, int nb){
    int taille;
    int *binary;
    int same = 1; //VRAI
    binary = GetBinaryCode(nb,&taille);
    if(taille!=m.rows){
        int* tmp = (int*)malloc(m.rows*sizeof(int));
        for(int i=0;i<m.rows;i++){
            if(i>=taille){
                tmp[i] = 0;
            }else{
                tmp[i] = binary[i];
            }
        }
        binary = tmp;
        taille = m.rows;
    }
    for(int i=0;i<m.cols;i++){
        for(int j=m.rows-1;j>=0;j--){
            if(m.data[i+m.cols*j]!=binary[taille-1-j]){
                same=0;
            }
        }
        if(same){
            return i;
        }else{
            same = 1;
        }
    }
    return -1;
}

void TransformControlMat(matrice h){
    int nb_col = 0;
    int* tab_value_identity = (int*)malloc(5*sizeof(int)); //fait pour un max de matrice de hauteur 5
    tab_value_identity[0] = 1;
    tab_value_identity[1] = 2;
    tab_value_identity[2] = 4;
    tab_value_identity[3] = 8;
    tab_value_identity[4] = 16;
    for(int i=0;i<h.rows;i++){
        nb_col = FindColOfBinary(h,tab_value_identity[i]);
        Permutation(h,nb_col,h.cols-1-i);
    }
    free(tab_value_identity);
}

matrice GetPtrans(matrice h){
    int j=0;
    int min = h.cols-h.rows-1;
    int max = min + h.rows;
    matrice p = NewMatrice(h.cols-h.rows,h.rows);
    for(int i=0;i<h.cols*h.rows;i++){
        if((i>min)&&(i<=max)){
            if(i==max){
                max += min + h.rows +1;
                min += h.cols;
            }
        }else{
            p.data[j] = h.data[i];
            j++;
        }
    }
    return p;
}

matrice Transpose(matrice m){
    matrice trans = NewMatrice(m.rows,m.cols);
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<m.cols;j++){
            trans.data[i+j*trans.cols] = m.data[j+i*m.cols];
        }
    }
    return trans;
}

void CompleteG(matrice g, matrice p){
    int iforp = 0;
    for(int i=g.cols-p.cols;i<g.cols;i++){
        for(int j=0;j<g.rows;j++){
            g.data[i+j*g.cols] = p.data[iforp+j*p.cols];
        }
        iforp++;
    }
}

matrice ProduitMatriciel(matrice a, matrice b){
    if(a.cols!=b.rows){
        printf("Produit matriciel indéfini !\n");
        exit(EXIT_FAILURE);
    }
    matrice res = NewMatrice(b.cols,a.rows);
    int result = 0;
    for(int i=0;i<a.rows;i++){
        for(int j=0;j<res.cols;j++){
            for(int k=0; k<a.cols;k++){
                result += a.data[k+i*a.cols]*b.data[j+k*b.cols];
            }
            res.data[j+i*res.cols] = result%2;
            result = 0;
        }
    }
    return res;
}