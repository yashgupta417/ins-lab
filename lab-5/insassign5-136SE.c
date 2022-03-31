#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Playfair Cypher
 */

int MAX_INPUT=1000;
int MATRIX_DIMENSION=5;
char FILLER='x';
// The reason of using dynamic 1D or 2D arrays is that:
// 1. they can be used across different functions
// 2. we can define their size at runtime
char** generateKeyMatrix(char* keyString) {
    char** keyMatrix=malloc(sizeof(char*)*MATRIX_DIMENSION);
    for(int i=0;i<MATRIX_DIMENSION;i++){
        keyMatrix[i]=malloc(sizeof(char)*MATRIX_DIMENSION);
    }
    int len=strlen(keyString)-1,cnt1=0,cnt2=0;
    for(int i=0;i<len;i++) {
        if (keyString[i]=='j') keyString[i]='i';
    }
    int isAdded[26]={0};
    isAdded['j'-'a']=1;
    for(int i=0;i<MATRIX_DIMENSION;i++){
        for(int j=0;j<MATRIX_DIMENSION;j++){
            if(cnt1<len) {
                if (isAdded[keyString[cnt1]-'a']) {
                    cnt1++; j--;
                } else {
                    isAdded[keyString[cnt1]-'a']=1;
                    keyMatrix[i][j]=keyString[cnt1++];
                }
            } else {
                if (isAdded[cnt2]) {
                    cnt2++; j--;
                } else {
                    isAdded[cnt2]=1;
                    keyMatrix[i][j]='a'+(cnt2++);
                }
            }
        }
    }

    printf("Matrix:\n");
    for(int i=0;i<MATRIX_DIMENSION;i++){
        for(int j=0;j<MATRIX_DIMENSION;j++){
            printf("%c ",keyMatrix[i][j]);
        }
        printf("\n");
    }
    return keyMatrix;
}

int** createCharToRowColumnMapping(char** keyMatrix) {
    int** mapping=malloc(sizeof(int*)*26);
    for(int i=0;i<26;i++){
        mapping[i]=malloc(sizeof(int)*2);
    }
    // printf("Mapping: \n");
    for(int i=0;i<MATRIX_DIMENSION;i++){
        for(int j=0;j<MATRIX_DIMENSION;j++){
            mapping[keyMatrix[i][j]-'a'][0]=i;
            mapping[keyMatrix[i][j]-'a'][1]=j;
            // printf("char=%c %d %d\n",keyMatrix[i][j],mapping[keyMatrix[i][j]-'a'][0], mapping[keyMatrix[i][j]-'a'][1]);
        }
    }
    return mapping;
}

void freeKeyMatrix(char** keyMatrix) {
    for(int i=0;i<MATRIX_DIMENSION;i++){
        free(keyMatrix[i]);
    }
    free(keyMatrix);
}
void freeMapping(int** mapping) {
    for(int i=0;i<26;i++){
        free(mapping[i]);
    }
    free(mapping);
}


char* processText(char* text) {
    int len=strlen(text)-1; //subtracting 1 to tackle '\n' added while taking input
    for(int i=0;i<len;i++) {
        if (text[i]=='j') text[i]='i';
    }
    char* pText=malloc(sizeof(char)*(2*len+1));
    int j=0;
    for(int i=0;i<len;){
        pText[j++]=text[i++];
        if(i==len || text[i]==text[i-1]){
            pText[j++]=FILLER;
        } else {
            pText[j++]=text[i++];
        }
    }
    pText[j]='\0';
    printf("Processed text: ");
    puts(pText);
    return pText;
}

char* encrypt(char* text, char* key){
    char* pText=processText(text);
	int len=strlen(pText);
    char* cypher=malloc(sizeof(char)*(len+1));
    char** keyMatrix=generateKeyMatrix(key);
    int** mapping=createCharToRowColumnMapping(keyMatrix);
	for(int i=0;i<len;){
        int col1=mapping[pText[i]-'a'][1];
        int col2=mapping[pText[i+1]-'a'][1];
        int row1=mapping[pText[i]-'a'][0];
        int row2=mapping[pText[i+1]-'a'][0];
        if (row1==row2) {
            cypher[i++]=keyMatrix[row1][(col1+1)%5];
            cypher[i++]=keyMatrix[row2][(col2+1)%5];
        } else if (col1==col2) {
            cypher[i++]=keyMatrix[(row1+1)%5][col1];
            cypher[i++]=keyMatrix[(row2+1)%5][col2];
        } else {
            cypher[i++]=keyMatrix[row1][col2];
            cypher[i++]=keyMatrix[row2][col1];
        }
	}
	cypher[len]='\0';
    freeKeyMatrix(keyMatrix);
    freeMapping(mapping);
    free(pText);
	return cypher;
}

char* decrypt(char* cypher, char* key){
	int len=strlen(cypher)-1; //subtracting 1 to tackle '\n' added while taking input
    char* text=malloc(sizeof(char)*(len+1));

    char** keyMatrix=generateKeyMatrix(key);
    int** mapping=createCharToRowColumnMapping(keyMatrix);
    for(int i=0;i<len;){
        int col1=mapping[cypher[i]-'a'][1];
        int col2=mapping[cypher[i+1]-'a'][1];
        int row1=mapping[cypher[i]-'a'][0];
        int row2=mapping[cypher[i+1]-'a'][0];
        if (row1==row2) {
            text[i++]=keyMatrix[row1][(col1-1+5)%5];
            text[i++]=keyMatrix[row2][(col2-1+5)%5];
        } else if (col1==col2) {
            text[i++]=keyMatrix[(row1-1+5)%5][col1];
            text[i++]=keyMatrix[(row2-1+5)%5][col2];
        } else {
            text[i++]=keyMatrix[row1][col2];
            text[i++]=keyMatrix[row2][col1];
        }
    }
    text[len]='\0';
    freeKeyMatrix(keyMatrix);
    freeMapping(mapping);
	return text;
}

int job(){
	printf("PLAYFAIR CYPHER\nSelect an option\n[1] Encrypt text\n[2] Decrypt cypher\n[3] Exit\n");
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