#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Monoalphabetic Cypher
 */

int MAX_INPUT=1000;

char* encrypt(char* text, char* key){
	int len=strlen(text);
	char* cypher=malloc(sizeof(char)*len);
	for(int i=0;i<len;i++){
		if (!isalpha(text[i])){
			cypher[i]=text[i];
			continue;
		}
		int begin=97;
		if (isupper(text[i]))
			begin=65;
		cypher[i]=key[text[i]-begin];
	}
	cypher[len]='\0';
	return cypher;
}

char* decrypt(char* cypher, char* key){
	int len=strlen(cypher);
        char* text=malloc(sizeof(char)*len);
	char* reverseKey=malloc(sizeof(char)*27);
	for(int i=0;i<26;i++){
		reverseKey[key[i]-65]=(char)97+i;
	}
	reverseKey[26]='\0';
        for(int i=0;i<len;i++){
                if (!isalpha(cypher[i])){
                        text[i]=cypher[i];
                        continue;
                }
                int begin=97;
                if (isupper(cypher[i]))
                        begin=65;
                text[i]=reverseKey[cypher[i]-begin];
        }
        text[len]='\0';
	return text;
}

int job(){
	printf("Select an option\n[1] Encrypt text\n[2] Decrypt cypher\n[3] Exit\n");
	int choice;
	scanf("%d",&choice);getchar();
	char* cypher, *text, *key;
	key=malloc(sizeof(char)*27);
	switch(choice) {
		case 1: ;
			text=malloc(sizeof(char)*MAX_INPUT);
			printf("Enter text: ");
			fgets(text, MAX_INPUT, stdin);
			printf("Key: ");
                        fgets(key, 27, stdin);
			cypher=encrypt(text, key);

			printf("Encrypting......\n");
			printf("Encrypted text: ");
			puts(cypher);
			printf("\n");

			free(text);
			free(cypher);
			free(key);
			break;
		case 2: ;
			cypher=malloc(sizeof(char)*MAX_INPUT);
                        printf("Enter cypher: ");
                        fgets(cypher, MAX_INPUT, stdin);
                        printf("Key: ");
                        fgets(key, 27, stdin);
                        text=decrypt(cypher, key);
			
                        printf("Decrypting......\n");
                        printf("Decrypted text: ");
			puts(text);
			printf("\n");

			free(cypher);
			free(text);
			free(key);
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
