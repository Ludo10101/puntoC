#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[] ){

    char s[100];
    FILE *f;
    if(argc!=2){
        printf("[ERRORE]:\nInserisci un file.txt\n");
    }
    f=fopen(argv[1],"r");
    fgets(s,sizeof(s),f);
    printf("%s",s);



    return 0;
}
