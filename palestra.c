#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANNO 2025

struct attrezzo{
    char nome[50];
    char zona[30];
    int anno_acquisto;
    float costo;
    int ore_utilizzo_giornaliere;
};
struct attrezzo * lettura(FILE *f,int *contatore){
    struct attrezzo* letti;
    struct attrezzo buf;
    char s[100];
    int max=10;
    int nletti;
    

    letti=malloc(sizeof(struct attrezzo)*max);

    while(fgets(s,sizeof(s),f)){
        s[strcspn(s,"\n")]='\0';
        if(*contatore==max-1){
            max=max*2;
            struct attrezzo *temp=realloc(letti,sizeof(struct attrezzo)*max);
            if(temp==NULL){
                printf("[ERRORE]\nAllocazione non andata a buon fine\n");
                exit(2);
            }
            letti=temp;
        }
        nletti=sscanf(s,"%[^;];%[^;];%d;%f;%d",buf.nome,buf.zona,&buf.anno_acquisto,&buf.costo,&buf.ore_utilizzo_giornaliere);
        if(nletti==5){
            letti[*contatore]=buf;
            *contatore=(*contatore)+1;
        }


    }

    struct attrezzo *temp1=realloc(letti,sizeof(struct attrezzo)*(*contatore));
            if(temp1==NULL){
                printf("[ERRORE]\nAllocazione non andata a buon fine\n");
                exit(2);
            }
            letti=temp1;
    return letti;
}
int compare(const void* a, const void *b){
    struct attrezzo atr_a=*(struct attrezzo *)a;
    struct attrezzo atr_b=*(struct attrezzo *)b;
    int ris;
    ris=-(atr_a.costo-atr_b.costo);
    return ris;
}

void mostra_per_zona(struct attrezzo * acquisiti,int *contatore){
    int zona_esistente=0; //se non esiste vale 0 altrimenti 1
    int i;
    char *vett_zone[20];
    int j;
    int count=1;
    vett_zone[0]=acquisiti[0].zona;


    for(i=0;i<*contatore;i++){
        zona_esistente=0;
        for(j=0;j<count;j++){
            if((strcmp(acquisiti[i].zona,vett_zone[j])==0)){
                zona_esistente=1;
                break;
            }
        }
        if(zona_esistente==0){
            vett_zone[count]=acquisiti[i].zona;
            count++;
            }
    }

    printf("[ZONE]\n");
    for(i=0;i<count;i++){
        printf("%s\n",vett_zone[i]);
    }
    int a;// variabile che mi serve per fare una bella stampa numerata
    for(i=0;i<count;i++){
        printf("\n[ZONA]\n[%s]\n",vett_zone[i]);
        a=0;
        for(j=0;j<*contatore;j++){
            if(strcmp(vett_zone[i],acquisiti[j].zona)==0){
                printf("%d)%s\n",a+1,acquisiti[j].nome);
                a++;
            }
        }
    }

}
int *attrezzo_piu_utilizzato(struct attrezzo * acquisiti,int * contatore,int *n){
    int i;
    int max;
    int *vett_oggetti_piu_utilizzati;
    vett_oggetti_piu_utilizzati=malloc(sizeof(int)*(*contatore));
    if(vett_oggetti_piu_utilizzati==NULL){
        printf("[ERRORE]\nErrore nell'allocazione della memoria\n");
        exit (3);
    }

    max=acquisiti[0].ore_utilizzo_giornaliere;
    for(i=1;i<(*contatore);i++){
        if(max<acquisiti[i].ore_utilizzo_giornaliere){
            max=acquisiti[i].ore_utilizzo_giornaliere;
        }
    }
    (*n)=0;
    for(i=0;i<(*contatore);i++){
        if(acquisiti[i].ore_utilizzo_giornaliere==max){
            vett_oggetti_piu_utilizzati[*n]=i; 
            (*n)++;//n si incrementa solo se abbiamo trovato un oggetto che ha il max di ore di utilizzo
        }
    }


    return vett_oggetti_piu_utilizzati;
}

void ammortamento(struct attrezzo * acquisiti,int contatore,char s[]){
    int i;
    int indice;
    float ore_tot;
    float costo_per_ora;

    for(i=0;i<contatore;i++){
        if(strcmp(s,acquisiti[i].nome)==0){
            indice=i;
            break;
        }
    }


    ore_tot=((ANNO-acquisiti[indice].anno_acquisto)*365*(acquisiti[indice].ore_utilizzo_giornaliere));
    costo_per_ora=(acquisiti[indice].costo)/(ore_tot);
    printf("[AMMORTAMENTO]\n");
    printf("%f\n",costo_per_ora);
}
int main(int argc,char* argv[]){
    int contatore=0;
    int i;
    int n;//intero che mi serve per tenere conto della i-esima posizione del vettore vett_oggetti_piu utilizzati
    struct attrezzo* acquisiti;
    int *vett_oggetti_piu_utilizzati;
    char s[100];
    
    if(argc!=2){
        printf("[ERRORE]\nInserisci un file.txt");
        return 1;
    }
    FILE *f;
    f=fopen(argv[1],"r");
    
    if(f==NULL){
        printf("[ERRORE]\nIl file non si è aperto correttamente\n");
        return 3;
    }
    acquisiti=lettura(f,&contatore);
    printf("[ATTREZZI PALESTRA]\n");
    for(i=0;i<(contatore);i++){
        printf("%d) %s %s %d %f %d\n",i+1, acquisiti[i].nome,acquisiti[i].zona,acquisiti[i].anno_acquisto,acquisiti[i].costo,acquisiti[i].ore_utilizzo_giornaliere);
    }
    puts("");
    qsort(acquisiti,contatore,sizeof(struct attrezzo),compare);

    printf("[ATTREZZI PALESTRA ORDINATI PER COSTO]\n");
    for(i=0;i<(contatore);i++){
        printf("%d) %s %s %d %f %d\n",i+1, acquisiti[i].nome,acquisiti[i].zona,acquisiti[i].anno_acquisto,acquisiti[i].costo,acquisiti[i].ore_utilizzo_giornaliere);
    }
    puts("");
    mostra_per_zona(acquisiti,&contatore);
    n=0;
    vett_oggetti_piu_utilizzati=attrezzo_piu_utilizzato(acquisiti, &contatore,&n);
    puts("");
    printf("[OGGETTI PIU' UTILIZZATI]\n");
    for(i=0;i<n;i++){
        printf("%s %d ore/giornaliere\n",acquisiti[vett_oggetti_piu_utilizzati[i]].nome,acquisiti[vett_oggetti_piu_utilizzati[i]].ore_utilizzo_giornaliere);
    }
    puts("");
    printf("Inserisci un attrezzo di cui vuoi calcolare l'ammortamento\n");
    fgets(s,sizeof(s),stdin);
    s[strcspn(s,"\n<")]='\0';
    puts("");
    ammortamento(acquisiti,contatore,s);

    free(vett_oggetti_piu_utilizzati);
    free(acquisiti);
    fclose(f);
    return 0;
}