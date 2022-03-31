#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Polyalphabetic Cypher
 */

int MAX_INPUT=1000;

char* encrypt(char* text, char* key){
	int len=strlen(text);
    int key_len=strlen(key)-1;
	char* cypher=malloc(sizeof(char)*len);
	for(int i=0,j=0;i<len;i++,j++){
		if (!isalpha(text[i])){
			cypher[i]=text[i];
			j--;
			continue;
		}
		int begin=isupper(text[i]) ? 65 : 97;
        int begin_k=isupper(key[j%key_len]) ? 65 : 97;
	
		cypher[i]=begin+(text[i]-begin+key[j%key_len]-begin_k)%26;
	}
	cypher[len]='\0';
	return cypher;
}

char* decrypt(char* cypher, char* key){
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
	char* cypher, *text, *key;
	key=malloc(sizeof(char)*MAX_INPUT);
	switch(choice) {
		case 1: ;
			text=malloc(sizeof(char)*MAX_INPUT);
			printf("Enter text: ");
			fgets(text, MAX_INPUT, stdin);
			printf("Key: ");
            fgets(key, MAX_INPUT, stdin);
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
            fgets(key, MAX_INPUT, stdin);
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