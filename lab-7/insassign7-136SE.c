#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void generateKey(){
    system("cat /dev/urandom | head -1 > x.bin");
    system("xxd -ps x.bin > x.txt");
    system("sed ':a; N; $!ba; s/\\\n//g; s/\\$//' x.txt | cut -c 1-16");
    printf("Key generated successfully!\n\n");
}

void encrypt(char* key){
    char* encryptCommand=malloc(100*sizeof(char));
    printf("Using plaintext.txt....\n");
    sprintf(encryptCommand, "openssl enc -des-cbc -in plaintext.txt -out cypher.enc -nosalt -iv 0000000000000000 -K %s", key);
    system(encryptCommand);
    system("xxd -ps cypher.enc");
    printf("Encryption Done!\n\n");
}

void decrypt(char* key){
    char* decryptCommand=malloc(100*sizeof(char));
    printf("Using cypher.enc....\n");
    sprintf(decryptCommand, "openssl enc -d -des-cbc -in cypher.enc -out decryptedtext.txt -nosalt -iv 0000000000000000 -K %s", key);
    system(decryptCommand);
    system("cat decryptedtext.txt");
    printf("\nDecryption Done!\n\n");
}

int job(){
	printf("DES using OpenSSL\nSelect an option\n[1] Encrypt\n[2] Decrypt\n[3] Generate Key\n[4] Exit\n");
	int choice;
	scanf("%d",&choice);getchar();
	char* key;
	switch(choice) {
		case 1: ;
            key=malloc(sizeof(char)*20);
			printf("Enter Key: ");
            fgets(key, 20, stdin);
            encrypt(key);
            free(key);
			break;
		case 2: ;
            key=malloc(sizeof(char)*20);
			printf("Enter Key: ");
            fgets(key, 20, stdin);
            decrypt(key);
            free(key);
			break;
        case 3: ;
            generateKey();
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