#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
struct libro{
    char titolo[100];
    char autore[100];
    int anno;
    char isbn[14];
    char stato;  //disponibile o prestato
};

struct libro * acquisizione(FILE *f,int *n){
    struct libro * presi;
    struct libro buf;
    int letti;
    int max;
    char s[100];
    max=3;
    presi=malloc(sizeof(struct libro)*max);
    while(fgets(s,sizeof(s),f)){
        if(*n==max-1){
            max=max*2;
            presi=realloc(presi,sizeof(struct libro)*(max));
        }
        letti=sscanf(s,"%[^;];%[^;];%d;%[^;]",buf.titolo,buf.autore,&buf.anno,buf.isbn);
        if(letti==4){
            presi[*n]=buf;
            (*n)++;
        }
    }
    presi=realloc(presi,sizeof(struct libro)*(*n));
        return presi;

}
// Questa funzione restituisce un puntatore ad intero, cioè un vettore di interi con l'allocazione dinamica
//questo vettore conterrà la posizione(possono essere anche di piu è per questo che è un vettore) del libro cercato
//nel vettore acquisiti del main
int * ricerca(struct libro * acquisiti,int dim,char isbn[14],int *nlib ){
    int n;
    int max;
    int *vett;
    n=0;
    max=3;
    vett=malloc(sizeof(int)*max);
    if(!vett) return NULL;
    
    for(int i=0;i<dim;i++){
        acquisiti[i].stato='n'; //mettiamo di default non disponibile
        if(strcmp(acquisiti[i].isbn,isbn)==0){
            acquisiti[i].stato='d';//se è disponibile lo stato diventerà 'd'
            
            if(n==max-1){
                max=max*2;
                vett=realloc(vett,sizeof(int)*(max));
            }
            vett[n]=i; //l'indice della casella dove viene trovato il libro viene salvato in vett
            n++;
        }
    }

    *nlib=n;
    vett=realloc(vett,sizeof(int)*n);
    return vett;
}

int main(int argc,char *argv[]){
    int contatore=0;
    int nlib;
    char s[100];
    struct libro *acquisiti;
    int *vett;
    int i;

    if(argc!=2){
        printf("[ERRORE]\nInserisci un file.txt\n");
        return 1;
    }
    FILE *f;
    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("[ERRORE]\nImpossibile aprire il file\n");
        return 2;
    }

    acquisiti=acquisizione(f,&contatore);
    printf("%d\n", contatore);
    puts("[ACQUISITI]");
    for(i=0; i<contatore;i++){
        printf("%s %s %d %s\n",acquisiti[i].titolo,acquisiti[i].autore,acquisiti[i].anno,acquisiti[i].isbn);
    }
    printf("[CONTROLLO DISPONIBILITA']\nInscerisci l'ISBN del libro cercato\n");
    fgets(s,sizeof(s),stdin);
    s[strcspn(s,"\n")]=0;
    vett=ricerca(acquisiti,contatore,s,&nlib); //vett conterrà gli indici del vettore acquisiti in cui è presente il libro cercato
    /*
    printf("[DEBUG]\n");
    printf("%d\n",nlib);
    for(i=0;i<nlib;i++){
        printf("%d\n",vett[i]);
    }
    printf("%d\n",vett[0]-1);
    printf("%c",acquisiti[vett[0]-1].stato);
    */
    if(acquisiti[vett[0]].stato=='n'){
        printf("[STATO]\nNon disponibile\n");
    }else if(acquisiti[vett[0]].stato=='d'){
        printf("[STATO]\nDisponibile\n");
    }else{
        printf("Errore nello stato\n");
    }
    printf("[LIBRO]\n");
    printf("%s %s %d %s %c\n",acquisiti[vett[0]].titolo,acquisiti[vett[0]].autore,acquisiti[vett[0]].anno,acquisiti[vett[0]].isbn,acquisiti[vett[0]].stato);
    printf("[Disponibilita']\nNumero di libri disponibili:%d\n",nlib);
    
    printf("[NUMERO LIBRI]\n");
    for(int i=0;i<nlib;i++){
        printf("I libri sono il numero: %d\n",vett[i]+1);
    }
    

    free(acquisiti);
    fclose(f);
    free(vett);


    return 0;
}