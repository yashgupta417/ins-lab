#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct Client{
    int private_key;
    int public_key;
    int secret_key;
};

struct DH_exchange{
    int G;
    int P;
    int public_key_a;
    int public_key_b;
};

void perform_DH_key_exchange(struct DH_exchange *dh, struct Client *A, struct Client *B){
    printf("Enter value of G(primitive root of P) and P(prime): "); // Example input: 9 23
    scanf("%d %d",&(dh->G),&(dh->P));
    printf("Enter private key for Client A: "); // Example input: 4
    scanf("%d",&(A->private_key));
    printf("Enter private key for Client B: "); // Example input: 3
    scanf("%d",&(B->private_key));

    printf("\n\nPrivate key of Client A: %d", A->private_key);
    printf("\nClient A generating its public key..........\n");
    A->public_key=(int)pow(dh->G,A->private_key)%dh->P;
    dh->public_key_a=A->public_key;
    printf("Generated public key of Client A: %d", A->public_key);

    printf("\n\nPrivate key of Client A: %d", B->private_key);
    printf("\nClient B generating its public key..........\n");
    B->public_key=(int)pow(dh->G,B->private_key)%dh->P;
    dh->public_key_b=B->public_key;
    printf("Generated public key of Client B: %d", B->public_key);

    printf("\n\nPassing public key of Client B to Client A and vice-versa......");

    printf("\n\nGenerating secret key at Client A.......\n");
    A->secret_key=(int)pow(dh->public_key_b,A->private_key)%dh->P;
    printf("Secret key generated at Client A: %d", A->secret_key);    

    printf("\n\nGenerating secret key at Client B.......\n");
    B->secret_key=(int)pow(dh->public_key_a,B->private_key)%dh->P;
    printf("Secret key generated at Client B: %d\n", B->secret_key); 
}

void DES_encrypt(int pass){
    char* encryptCommand=(char*)malloc(100*sizeof(char));
    system("printf \"\nMessage: \" ");
    system("cat plaintext.txt");
    sprintf(encryptCommand, "openssl enc -des-cbc -in plaintext.txt -out cypher.enc -pbkdf2 %d 2>/dev/null", pass);
    system(encryptCommand);
    system("printf \"\nEncrypted Message: \" ");
    system("xxd -ps cypher.enc");
    printf("Encryption Done!\n\n");
}

void DES_decrypt(int pass){
    char* decryptCommand=(char*)malloc(100*sizeof(char));
    sprintf(decryptCommand, "openssl enc -d -des-cbc -in cypher.enc -out decryptedtext.txt -pbkdf2 %d 2>/dev/null", pass);
    system(decryptCommand);
    system("printf \"\nDecrypted Messsage: \" ");
    system("cat decryptedtext.txt");
    printf("\nDecryption Done!\n\n");
}

int main(){
    struct Client A,B;
    struct DH_exchange dh;
    perform_DH_key_exchange(&dh,&A,&B);
    system("printf \"\nEncrypt message at Client A.....\" ");
    DES_encrypt(A.secret_key);
    system("printf \"\nSending message.......\n\" ");
    system("printf \"\n\nDecrypting message at Client B......\" ");
    DES_decrypt(B.secret_key);
}
