#include <stdio.h>
#include <stdlib.h>

int get_bit(int a,int pos){
    return a & (1<<pos);
}

int set_bit(int a,int pos){
    return a|(1<<pos);
}

void division_euc(int mot,int gen,int t_mot,int t_gen,int* res,int* t_res){
    int tmp,t_tmp;
    while(t_mot>=t_gen){
        tmp=0;
        t_tmp=t_mot-t_gen;
        for(int i=0;i<t_gen;i++){
            if(get_bit(gen,t_gen-1-i)!=0)tmp=set_bit(tmp,t_tmp-1+t_gen-i);
        }
        mot=mot^tmp;
        while(get_bit(mot,t_mot-1)==0 && t_mot>0)t_mot--;
    }
    *res=mot;
    *t_res=t_mot;
    return;
}


int main(int argc,char** argv){
    if(argc!=3){
        printf("Syntaxe : %s [ mot a coder ] [ polynome générateur ] ( tout doit etre sous forme binaire )\n",argv[0]);
        return EXIT_FAILURE;
    }

    int taille_m=0,taille_p=0,mot=0,poly=0;


    for (int i=0; argv[2][i] != '\0'; taille_p++,i++);
    for(int i=0;i<taille_p;i++){
        if(argv[2][i]=='1')poly=set_bit(poly,taille_p-1-i);
    }


    for (int i=0; argv[1][i] != '\0'; taille_m++,i++);
    for(int i=0;i<taille_m;i++){
        if(argv[1][i]=='1')mot=set_bit(mot,taille_m-1-i+taille_p-1);
    }

    taille_m+=taille_p-1;

    int code,taille_c;

    division_euc(mot,poly,taille_m,taille_p,&code,&taille_c);

    for(int i=0;i<taille_c;i++){
        printf("%d",get_bit(code,taille_c-1-i)!=0);
    }
    printf("\n");

    code= code ^ (mot);
    taille_c= taille_m;

    for(int i=0;i<taille_c;i++){
        printf("%d",get_bit(code,taille_c-1-i)!=0);
    }
    printf("\n");

    return 0;
}