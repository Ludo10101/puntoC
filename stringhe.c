#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trova_carattere(char * stringa, char c){
    int i=0;
    int lun=strlen(stringa);
    for(i=lun;i>=0;i--){
        if(stringa[i]==c){
            return i;
        }
    }
    return -1;
}
void basename(char * stringa,char* b){
    int p=0;
    p=trova_carattere(stringa, '/');
    if(p!=-1){
        strcpy(b,stringa+p+1);
    }else{
        strcpy(b,"la stringa non contiene il carattere '/'");
    }
}
void dirname(char * stringa, char b[]){
    int p=trova_carattere(stringa, '/');
    
    if(p>=0){
        strcpy(b,stringa);
        b[p]='\0';
    }else{
        strcpy(b,"La stringa non contiene il carattere '/'");
    }
      
}
int tipo(char *stringa){
    if(stringa[0]=='/'){
        return 1;
    }else{
        return 0;
    }
}
char * estensione(char * stringa, char b[]){
    int pos_punto=trova_carattere(stringa, '.');
    int pos_slash=trova_carattere(stringa,'/');

    if(pos_punto>pos_slash){
        strcpy(b,stringa+pos_punto+1);
    }
    if(pos_slash>pos_punto){
        strcpy(b,"nessuna");
    }
    if((pos_slash==pos_punto) && (pos_slash==-1)){
        strcpy(b,"nessuna");
    }
    return b;

}
int main(int argc,char * argv[]){
    if(argc!=2){
        printf("[ERRORE]\nInserisci un parametro (stringa)\n");
        exit(1);
    }
    char * stringa=argv[1];
    char b[100];
    basename(stringa,b);
    printf("[BASENAME]\n%s\n",b);
    dirname(stringa,b);
    printf("[DIRNAME]\n%s\n",b);
    printf("[TIPO]\n");
    if(tipo(stringa)==1){
        printf("assoluto\n");
    }else{
        printf("relativo\n");
    }
    printf("[ESTENSIONE]\n");
    estensione(stringa,b);
    printf("%s\n",b);


    return 0;
}