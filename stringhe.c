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

    return 0;
}