#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Polyalphabetic Cypher
 */

int MAX_INPUT=1000;
int keySize=3;
int key[3][3]={{17,7,5},{21,18,21},{2,2,19}};
int keyInv[3][3]={{8,17,1},{17,21,12},{22,22,11}};

char* encrypt(char* text){
	int len=strlen(text)-1; text[len]='/0';

    // appending bogus char 'x' if required
    int _len=len+len%keySize;
    char* _text=malloc(sizeof(char)*(_len+1));
    strcpy(_text,text);
    for(int i=0;i<=len%keySize;i++){
        _text[len+i]='x';
    }
    _text[_len]='\0';

    int* _cypher=calloc(_len,sizeof(int));
    char* cypher=malloc(sizeof(char)*(_len+1));

    // matrix multiplication
	for(int i=0;i<_len;i+=3){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                _cypher[i+j]+=key[k][j]*(toupper(_text[i+k])-65);
            }
        }
	}

    for(int i=0;i<_len;i++){
        cypher[i]=(_cypher[i]+26*100)%26+65;
    }
	cypher[_len]='\0';
	return cypher;
}

char* decrypt(char* cypher){
	int len=strlen(cypher);
    int key_len=strlen(key)-1;
    char* text=malloc(sizeof(char)*len);
    for(int i=0,j=0;i<len;i++,j++){
        if (!isalpha(cypher[i])){
                text[i]=cypher[i];
				j--;
                continue;
        }
        int begin=isupper(cypher[i]) ? 65 : 97;
        int begin_k=isupper(key[j%key_len]) ? 65 : 97;
    
        text[i]=begin+(cypher[i]-begin-(key[j%key_len]-begin_k)+26)%26;
    }
    text[len]='\0';
	return text;
}

int job(){
	printf("POLYALPHABETIC CYPHER\nSelect an option\n[1] Encrypt text\n[2] Decrypt cypher\n[3] Exit\n");
	int choice;
	scanf("%d",&choice);getchar();
	char* cypher, *text;
	switch(choice) {
		case 1: ;
			text=malloc(sizeof(char)*MAX_INPUT);
			printf("Enter text: ");
			fgets(text, MAX_INPUT, stdin);
			cypher=encrypt(text);

			printf("Encrypting......\n");
			printf("Encrypted text: ");
			puts(cypher);
			printf("\n");

			free(text);
			free(cypher);
			break;
		case 2: ;
			cypher=malloc(sizeof(char)*MAX_INPUT);
            printf("Enter cypher: ");
            fgets(cypher, MAX_INPUT, stdin);
            text=decrypt(cypher);

            printf("Decrypting......\n");
            printf("Decrypted text: ");
			puts(text);
			printf("\n");

			free(cypher);
			free(text);
			break;
		default:
			return 1;
	}
	return 0;	
}

int main(){
	while(1){
		int exit=job();
		if(exit) break;
	}
}