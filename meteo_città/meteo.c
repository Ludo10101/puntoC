#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
struct meteo{
    char nome_citta[100];
    int temperatura_massima;
    int temperatura_minima;
    char condizione_meteo[20];
};
struct meteo* lettura(FILE * f,int * contatore){
    struct meteo* letti;
    struct meteo buf;
    char s[100];
    int nletti;
    int max=3;

    letti=malloc(sizeof(struct meteo)*max);

    while(fgets(s,sizeof(s),f)){
        if(*contatore==max-1){
            max=max*2;
            letti=realloc(letti, sizeof(struct meteo)*max);
        }
        s[strcspn(s,"\n")]='\0';
        nletti=sscanf(s,"%[^;];%d;%d;%[^;]",buf.nome_citta,&buf.temperatura_massima,&buf.temperatura_minima,buf.condizione_meteo);
        if(nletti==4){
            letti[*contatore]=buf;
            *contatore=*contatore+1;
        }
    }
    letti=realloc(letti,sizeof(struct meteo)*(*contatore));
    return letti;
}
int compare(const void * a,const void * b){
    struct meteo a_str=*(struct meteo*)a;
    struct meteo b_str=*(struct meteo*)b;
    return(strcmp(a_str.nome_citta,b_str.nome_citta));
}

int main(int argc,char *argv[]){
    struct meteo *acquisiti;
    int contatore=0; 
    int i;
    
    FILE *f;
    f=fopen(argv[1],"r");
    if(argc!=2){
        printf("[ERRORE]\nInserisci un file.txt\n");
        return 1;
    }
    acquisiti=lettura(f,&contatore);
    puts("");
    puts("");
    puts("");
    printf("[ACQUISITI]\n");
    for(i=0;i<contatore;i++){
        printf("%s %d %d %s\n",acquisiti[i].nome_citta,acquisiti[i].temperatura_massima,acquisiti[i].temperatura_minima,acquisiti[i].condizione_meteo);
        puts("");
    }
    puts("");
    puts("");
    puts("");
    qsort(acquisiti,contatore,sizeof(struct meteo),compare);
    printf("[ACQUISITI ORDINATI]\n");
    for(i=0;i<contatore;i++){
        printf("%s %d %d %s\n",acquisiti[i].nome_citta,acquisiti[i].temperatura_massima,acquisiti[i].temperatura_minima,acquisiti[i].condizione_meteo);
        puts("");
    }

    fclose(f);
    free(acquisiti);
    
    return 0;
}