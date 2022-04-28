#include<stdio.h>
#include<stdlib.h>


int f(int n){
    return n*2;
}

int main(){
    char master_key[20] = "i-am-master-key";
    char shared_Key[20] = "i-am-shared-key";

    int n1=5, n2=11;
    
    //key distribution
    printf("DECENTRALISED KEY CONTROL...\n\n");

    char command[200];
    sprintf(command, "echo '%s,%d,%d' > text1.txt", shared_Key, f(n1), n2);
    system(command);
    
    sprintf(command, "openssl aes-128-cbc -e -in text1.txt -out cypher1.txt -pass pass:%s 2>/dev/null", master_key);
    system(command);

    sprintf(command, "openssl aes-128-cbc -d -in cypher1.txt -out decrypt1.txt -pass pass:%s 2>/dev/null", master_key);
    system(command);

    sprintf(command, "echo '%d' > text2.txt", f(n2));
    system(command);

    sprintf(command, "openssl aes-128-cbc -e -in text2.txt -out cypher2.txt -pass pass:%s 2>/dev/null", shared_Key);
    system(command);

    sprintf(command, "openssl aes-128-cbc -d -in cypher2.txt -out decrypt2.txt -pass pass:%s 2>/dev/null", shared_Key);
    system(command);

    printf("N2: %d, Value of f(N2): %d\n", n2, f(n2)); fflush(stdout);

    char str[10];
    FILE* file = fopen("decrypt2.txt", "r");
    fgets(str, 10, file);
    fclose(file);
    printf("f(N2) from initiator A: %s", str);

    printf("\nKEY DISTRIBUTION COMPLETED.\n");

    //communication using shared session key
    printf("\nUSING SHARED KEY FOR COMMUNICATION.\n");
    system("echo 'plaintext: '");
    system("cat text3.txt");

    //performing encryption using session key
    sprintf(command, "openssl aes-128-cbc -e -in text3.txt -out cypher3.txt -pass pass:%s  2>/dev/null", shared_Key);
    system(command);

    system("\n echo '\n\ncypher: ' ");
    system("cat cypher3.txt");

    //performing decryption using shared key
    sprintf(command, "openssl aes-128-cbc -d -in cypher3.txt -out decrypt3.txt -pass pass:%s  2>/dev/null", shared_Key);
    system(command);

    system("\n echo '\n\ndecrypt text: '");
    system("cat decrypt3.txt");

    printf("\n\nCOMMUNICATION DONE SUCCESSFULLY\n");
}