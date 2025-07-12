#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct studente{
    char nome[100];
    char cognome[100];
    int eta;
    float media;
};

struct studente * lettura(FILE *f,int * c){
    struct studente *letti;
    struct studente buf;
    int max;
    int nletti=0;
    int n=0;
    char s[200];
    max=3;

    letti=malloc(sizeof(struct studente)*max);
    
    
    while(fgets(s,sizeof(s),f)){
        if(*c==max-1){
            max=max*2;
            letti=realloc(letti,sizeof(struct studente)*max);
        }
        nletti=sscanf(s,"%s %s %d %f",buf.nome,buf.cognome,&buf.eta,&buf.media);
        
        if(nletti==4){
            letti[n]=buf;
            n++;
        }
    }
    letti=realloc(letti,sizeof(struct studente)*n);
    *c=n;
    return letti;
}


int main(int argc,char *argv[] ){
    int * n;
    int a;
    struct studente *s;
    a=15;
    n=&a;
    FILE *f;
    if(argc!=2){
        printf("[ERRORE]:\nInserisci un file.txt\n");
    }
    f=fopen(argv[1],"r");
    s=lettura(f,n);
    printf("[STUDENTI]:\n");

    printf("[ATTENZIONE]\n %s %s ", s[3].nome,s[3].cognome);
    
    for(int i=0;i<*n;i++){
        printf("%s %s %d %f\n",s[i].nome,s[i].cognome,s[i].eta,s[i].media);
    }

    free(s);
    return 0;

}