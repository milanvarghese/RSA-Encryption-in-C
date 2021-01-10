#include<stdio.h>
#include <math.h>
#include <string.h>
//Primality Test Algorithm
#include "Miller_Rabin.c"
//Modular multiplicative inverse
#include "inverse.c"

//Initalizing Variables
int p,q;
int n,phi;
int e,d;
char text[1000];
unsigned long int cypher[1000];
int sizecount=0,flagkey=0,flagencrypt=0;

//Basic Euclidean Algorithm for GCD
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b%a, a); 
} 
//Function to generate public and private key pairs
void generate_keypair(){
	jumb:
	system("cls");
	printf("\n-------------------------------------------------------------------------------------");
	printf("\nEnter Two Prime Numbers (Larger Pairs More Secure): ");
	scanf("%d%d",&p,&q);
	if(isPrime(p,4)==0 && isPrime(q,4)==0){
		printf("\nBoth Inputs Not Prime... Please Enter two Prime Numbers!");
		sleep(2);
		goto jumb;
	}else if(isPrime(p,4)==0 || isPrime(q,4)==0){
		printf("\nOne of the Inputs Not Prime... Please Enter two Prime Numbers!");
		sleep(2);
		goto jumb;
	}else if(p*q<=122){ //to include all alphabets in ascii we need to have p*q atleast 122
		printf("\nPrime Numbers too Small... Please Enter two larger Prime Numbers!");
		sleep(2);
		goto jumb;
	}else if(p==q){
		printf("\nPlease enter two differnt prime numbers!");
		sleep(2);
		goto jumb;
	}
	if(p*q<=255){
		printf("\nEnter two prime numbers whose product is larger than 255.");
		sleep(2);
		goto jumb;
	}
	
	printf("\n-------------------------------------------------------------------------------------");
	//n=pq
	n=p*q;
	//Phi is the totient of n
	phi=(p-1)*(q-1);
	int style;
	char word0[25]="Generating Key Pairs...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}
	
	sleep(1);
	int i;
	do{
		i=rand();
		if(isPrime(i,4)==1 && (i<phi)){
			e = i;
			break;
		}
	}while ((gcd(phi,e) != 1));
	d = modInverse(e, phi);
	
	printf("\n");
	char word1[100]="Please Take Note of the Public and Private Key Pairs: ";
	for(style=0;style<strlen(word1);style++){
		printf("%c",word1[style]);
		usleep(100000);
	}
	sleep(1);
	printf("\n\nEncryption Key (e,n) = (%d,%d)",e,n);
	printf("\nDecryption Key (d,n) = (%d,%d)\n",d,n);
	flagkey=1;
}

int encryption(int e, int n, int text){
	unsigned long int cypher;
	cypher =power(text,e,n);
	return cypher;
}

int decryption(int d, int n, int text){
	unsigned long int decrypt;
	decrypt = power(text,d,n);
	return decrypt;
}
int noofdigits(int a){
	int num=0;
	while(a!=0){
		a/=10;
		num+=1;
	}
	return num;
}
//Fuction to display the keys
void displaykeys(){
	if(flagkey==0){
		printf("\nNo encryption found, Please Encrypt some information!\n");
		sleep(2);
		system("cls");
		return;
	}
	printf("\n\nEncryption Key (e,n) = (%d,%d)",e,n);
	printf("\nDecryption Key (d,n) = (%d,%d)\n",d,n);
	sleep(2);
}
//Function to encrypt the text
void encryptText(){
	printf("\n-------------------------------------------------------------------------------------");
	int style;
	char word0[25]="Encryption Process...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}sleep(1);
	
	unsigned long int x,y;
	printf("\n\nEnter Encryption Key Pairs (e,n): ");
	scanf("%d%d",&x,&y);
	printf("\nEnter Message: ");
	gets(text);
	gets(text);
	
	int i=0,temp,tempcyp;
	for (i=0;i<sizeof(text);i++){
		temp=text[i]-'0'+48;

		tempcyp=encryption(x,y,temp);
		cypher[i]=tempcyp;
		sizecount++;
		if(text[i+1]=='\0')
			break;
	}
	printf("\nCypher: ");
	for(i=0;i<sizecount;i++)
		printf("%d ",cypher[i]);
	flagencrypt=1;
}
//Function to Decrypt the text
void decryptText(){
	if(flagencrypt==0){
		printf("\nPlease Encrypt before Decrypting!\n");
		sleep(2);
		system("cls");
		return;
	}
	printf("\n-------------------------------------------------------------------------------------");
	
	int i,style;
	char word0[25]="Decryption Process...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}sleep(1);
	
	unsigned long int x,y;
	printf("\n\nEnter Decryption Key Pairs (d,n): ");
	scanf("%d%d",&x,&y);
	
	printf("\nCypher: ");
	for(i=0;i<sizecount;i++)
		printf("%d ",cypher[i]);
	
	unsigned long int value;
	char tempdecyp;
	printf("\n\nDecypher: ");
	for(i=0;i<sizecount;i++){
		value=decryption(x,y,cypher[i]);
		tempdecyp=(char)value;
		printf("%c",value,tempdecyp);
		}
	printf("\n");
	sleep(3);
}
//Function to display the cypher
void displayCypher(){
	if(flagencrypt==0){
		printf("\nPlease encrypt some data to show its cypher!\n");
		sleep(2);
		system("cls");
		return;
	}
	int i;
	printf("\nCypher: ");
	for(i=0;i<sizecount;i++)
		printf("%d ",cypher[i]);
	sleep(2);
}
//Function for menu
void menu(){
	jumb:
	printf("\n-------------------------------------------------------------------------------------");
	printf("\nMenu - Rivest Shamir Adleman (RSA) Encryption");
	printf("\n-------------------------------------------------------------------------------------");
	printf("\n1. Key Pair Generation");
	printf("\n2. Encrypt Text");
	printf("\n3. Decrypt Text");
	printf("\n4. Display Cypher Text!");
	printf("\n5. Display Key Pairs!");
	printf("\n6. Clear Screen");
	printf("\n7. Exit");
	int menu;
	printf("\n\nEnter your choice: ");
	scanf("%d",&menu);
	switch(menu){
		case 1: generate_keypair();break;
		case 2: encryptText();break;
		case 3: decryptText();break;
		case 4: displayCypher();break;
		case 5: displaykeys();break;
		case 6: system("cls");break;
		case 7: exit(0);
		default: printf("\nWrong Input!");
				 sleep(1);
				 goto jumb;
	}
}
	
int main(){
	while(1)
		menu();
	return 0;
}
