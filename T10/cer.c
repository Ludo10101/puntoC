#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 5
#define NESSUNA 0
#define CONTENUTO -1
#define INTERSECA 1
#define CONTIENE 2
#define COINCIDE 3

struct cerchi{
	char nome[128];
	int x,y,r;
};
struct cerchi* carica_elenco(FILE *f,int *n);
void stampa(struct cerchi* letti, int n);
int compare(const void *a, const void *b){
	const struct cerchi *ac,*bc;
	ac=a;
	bc=b;
	if((ac->r)>(bc->r)) return 1;
	if((ac->r)<(bc->r)) return -1;
	else return 0;
}
float dist(struct cerchi a, struct cerchi b){
	float distanza;
	distanza=sqrt(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)));
	return distanza;
}
int relazioni( struct cerchi a, struct cerchi b){
	float distanza;
	distanza=dist(a,b);

	if(distanza>=(a.r+b.r)){
		return NESSUNA;	
	} 
	if(distanza<(a.r+b.r)){
		if(distanza==0&&a.r==b.r){
			return COINCIDE;	
		} 
		else if(distanza <=(a.r-b.r)){
			return CONTIENE;
		}else if((a.r-b.r) >0){
			return INTERSECA;
		}else if( (a.r-b.r)<0){
			return CONTENUTO;
		}
	
	}
	printf("ciao\n");
	return NESSUNA;
}
void rel(struct cerchi * letti, int n){
	char *relazione[4]={"NESSUNA","INTERSECA","CONTIENE","COINCIDE"};
	int i=0;
	int j=0;
	int rel=0;
	printf("[RELAZIONI]\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=j){
	
				rel=relazioni(letti[i],letti[j]);
		
					if(rel!=-1){
						printf("%s %s %s\n",letti[i].nome,relazione[rel],letti[j].nome);
								
								}	
			}
			
		}
	}
}
int main(int argc, char * argv[]){
	if(argc!=2){
		printf("[ERRORE]\nInserire un file.txt da riga di comando\n");
		exit(1);
	}
	int n=0;
	struct cerchi* letti;
	FILE* f; 
	f=fopen(argv[1],"r");

	letti=carica_elenco(f,&n);
	// 1) stampa
	stampa(letti,n);

	// 2) Ordinamento
	qsort(letti,n,sizeof(struct cerchi),compare);
	stampa(letti,n);

	// 3) Relazioni
	rel(letti,n);


	
	fclose(f);
	free(letti);	
	return 0;
}
struct cerchi* carica_elenco(FILE *f,int *n){
	struct cerchi* letti;
	struct cerchi buf;
	int max=MAX;
	char s[300];
	int n_letti;
	letti=malloc(sizeof(struct cerchi)*max);
	if(letti==NULL){
		printf("[ERRORE]\nAllocazione non andata a buon fine\n");
	}

	while(fgets(s,sizeof(s),f)){

		if((*n)>=max-1){
			max=max*2;
			struct cerchi * temp;
			temp=realloc(letti, sizeof(struct cerchi)*max);
			if(temp==NULL){
				printf("[ERRORE]\nPrima rellocazione non andata a buon fine\n");
			}
			letti=temp;
		}
	
		n_letti=sscanf(s,"%s %d %d %d",buf.nome,&buf.x,&buf.y,&buf.r);
		if(n_letti==4){
		
			letti[*n]=buf;
			(*n)=(*n)+1;
		}
	}
	struct cerchi * temp;
	temp=realloc(letti,sizeof(struct cerchi)*(*n));
	if(temp==NULL){
		printf("[ERRORE]\nPrima rellocazione non andata a buon fine\n");
	}
	letti=temp;
	return letti;
}
void stampa(struct cerchi* letti, int n){
	int i;
	printf("[CERCHI]\n");
	for(i=0;i<n;i++){
		printf("%s %d %d %d\n",letti[i].nome,letti[i].x,letti[i].y,letti[i].r);
	}
}
