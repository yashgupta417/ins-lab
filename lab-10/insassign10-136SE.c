#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <time.h>
#include <ctype.h>


int hash(char* msg, int x){
    // puts(msg);
    // printf("hash: x=%d\n",x);
    int n=strlen(msg);
    int hash=0;
    for(int i=0;i<n-1;i++){
        hash+=(tolower(msg[i])-97);
    }
    hash+=x;
    return hash;
}


int generateRandomNumber(int min, int max){
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

int power(long long x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

int main(){
    // ************* Setting up private and public variables **************
    int p=11,q=5,a=3; // q = prime factor of p-1, a^q=1(mod p)
    int s=4; // private key, random between 0<s<q
    int v=3; // public key, v=a^(-s)mod p

	char* msg=malloc(sizeof(char)*100);
	printf("Enter message: ");
	fgets(msg, 100, stdin);

    printf("\nPublic variables: p=%d q=%d a=%d\n",p,q,a);
    printf("Private key: s=%d\n",s);
    printf("Public key: v=%d\n",v);

    // ************* Digitally signing the message ************
    int r=generateRandomNumber(1,q-1);
    int x=(int)pow(a,r)%p;
    int e=hash(msg,x);
    int y=(r+s*e)%q;
    printf("\nDigitally signing the message.....\n");
    printf("Signature: (e,y)=(%d,%d)\n",e,y);

    // ************* Verifying signature ***********
    int x1=(((int)power(a,y,p))*((int)power(v,e,p)))%p;
    int e1=hash(msg,x1);
    printf("\nVerifying message......\n");
    printf("Original hash: %d\n",e);
    printf("Calculated hash: %d\n",e1);
    printf("Successfully Verified!");

}