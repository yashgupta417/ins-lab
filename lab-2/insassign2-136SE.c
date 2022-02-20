#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Caeser Cypher Encryption
 */

int MAX_INPUT=1000;

char* encrypt(char* text, int shift){
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
		cypher[i]=begin+(text[i]-begin+shift+26)%26;
	}
	cypher[len]='\0';
	return cypher;
}

char* decrypt(char* cypher, int shift){
	int len=strlen(cypher);
        char* text=malloc(sizeof(char)*len);
        for(int i=0;i<len;i++){
                if (!isalpha(cypher[i])){
                        text[i]=cypher[i];
                        continue;
                }
                int begin=97;
                if (isupper(cypher[i]))
                        begin=65;
                text[i]=begin+(cypher[i]-begin-shift+26)%26;
        }
        text[len]='\0';
	return text;
}

int job(){
	printf("Select an option\n[1] Encrypt text\n[2] Decrypt cypher\n[3] Exit\n");
	int choice, shift;
	scanf("%d",&choice);getchar();
	char* cypher, *text;
	switch(choice) {
		case 1: ;
			text=malloc(sizeof(char)*MAX_INPUT);
			printf("Enter text: ");
			fgets(text, MAX_INPUT, stdin);
			printf("Shift[-25 to 25]: ");
                        scanf("%d", &shift);
			if (shift<-25 || shift>25){
				printf("Invalid shift: %d\n", shift);
				return 0;
			}
			cypher=encrypt(text, shift);

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
                        printf("Shift[-25 to 25]: ");
                        scanf("%d", &shift);
                        if (shift<-25 || shift>25){
                                printf("Invalid shift: %d\n", shift);
                                return 0;
                        }
                        text=decrypt(cypher, shift);
			
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
