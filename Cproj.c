
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char a[26][26];
int row(char c){

    int i;
    for(i=0;i<26;i++){
        if(a[0][i]==c)
            return(i);
    }
}

int column(char c){
    int i;
    for(i=0;i<26;i++){
        if(a[i][0]==c)
            return(i);
    }
}

int decrypt_row(char c,int j){
    int i;
    for(i=0;i<26;i++){
        if(a[i][j]==c)
            return(i);
    }
}

void vernam_encrypt(){
	int n;
	
	char input[400], key[400],e_m[400];
	
	int i,j,value,x,y;
	value =96;
	for(i=0;i<26;i++){
		value++;
		for(j=0;j<26;j++){
			a[i][j]=value++;
			if(value == 123)
				value =97;
		}
	}

	FILE *f1, *f2, *f3;
	f1 = fopen("Text.txt","r");
	f2 = fopen("Key.txt","w");
	f3 = fopen("Encrypted.txt", "w");
	fscanf(f1,"%s",input);
	n=strlen(input);

	srand(time(NULL));
	for(i=0;i<n;i++){
		key[i]=rand()%26+97;
		fputc(key[i], f2);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			input[j]=tolower(input[j]);
		if(key[i]!='\0'){
                x=row(key[i]);
                y=column(input[i]);
                e_m[i]=a[y][x];
		}
		else
			break;
		if(input[i]==EOF)
			break;
	}
	e_m[i]='\0';
	fprintf(f3,"%s",e_m);
	fclose(f1);
	fclose(f2);
	fclose(f3);

}

void vernam_decrypt(){
	int n;
	//char a[26][26];
	char input[400],key[400],e_m[400],d_m[400];
	
	int i,j,value,x,y;
	value =96;
	for(i=0;i<26;i++){
		value++;
		for(j=0;j<26;j++){
			a[i][j]=value++;
			if(value == 123)
				value =97;
		}
	}
	FILE *f4, *f5, *f6;
	f4 = fopen("Encrypted.txt","r");
	f5 = fopen("Key.txt","r");
	f6 = fopen("Decrypted.txt", "w");

	fscanf(f4,"%s",e_m);
	fscanf(f5,"%s",key);
	n=strlen(e_m);
	for(i=0;i<n;i++){
		y=column(key[i]);
		x=decrypt_row(e_m[i],y);
		d_m[i]=a[x][0];
	}
	fprintf(f6,"%s",d_m);
	fclose(f4);
	fclose(f5);
	fclose(f6);

}

void Sub_encrypt(){
	FILE *fp, *fp1, *fp2;
	fp=fopen("Text.txt", "r");
	fp1=fopen("Encrypted.txt", "w");
	fp2=fopen("Key.txt", "w");	
	char in;
	int i, n, key[256];
	for(i=0;i<=255;i++)
		key[i]=0;
	srand(time(NULL));
	in=fgetc(fp);
	while(in!=EOF){
		int j=(int)in-1;
		if(key[j]==0){
			key[j]=rand()%255+1;
			for(i=0;i<255;i++){
				if(key[i]==key[j] && i!=j){
					key[j]++;
					if(key[j]==256)
						key[j]=0;
					i=0;
				}
			}
		}
		fputc(key[j], fp1);
		in=fgetc(fp);
	}
	for(i=0;i<256;i++)
		fputc((char)key[i], fp2);
	fclose(fp1);
	fclose(fp2);
	fclose(fp);
}


void Sub_decryptkey(){
	FILE *fp, *fp1, *fp2;
	fp1=fopen("Encrypted.txt", "r");
	fp2=fopen("Key.txt", "r");
	fp=fopen("Decrypted.txt", "w");
	char in;
	int i, key[256], j;
	for(i=0;i<256;i++){
		key[i]=(int)fgetc(fp2);
	}
	fclose(fp2);
	in=fgetc(fp1);
	while(in!=EOF){
		j=((int)in+256)%256;
		for(i=0;i<256;i++){
			if(key[i]==j){
				fputc((char)(i+1),fp);
				//printf("%c\n", (char)(i+1));
			}
		}
		//fputc(key[(int)in-1],fp);
		in=fgetc(fp1);
	}
	fclose(fp1);
	//fclose(fp2);
	fclose(fp);
}


void DecryptNo(){
	FILE *fp, *fp1, *fp2;
	fp=fopen("Encrypted.txt", "r");
	fp1=fopen("Decrypted.txt", "w");
	char in, in1, out[26], tab[26]={'e', 't', 'a', 'o', 'i', 'n', 's', 'r', 'h', 'd', 'l', 'u', 'c', 'm', 'f', 'y', 'w', 'g', 'p', 'b', 'v', 'k', 'x', 'q', 'j', 'z'};
	int i, a[26], x, l, r=0, j;
	in=fgetc(fp);
	in1=in;
	for(i=0;i<26;i++){
		a[i]=0;
		out[i]='0';
	}
	while(in!=EOF){
		in=toupper(in);
		if((int)in>=65 && (int)in<91){
			a[in-65]++;
		}
		in=fgetc(fp);
	}
	for(i=0;i<26;i++){
		x=0;
		for(j=0;j<26;j++){
			if(a[j]>x && out[j]=='0'){
				x=a[j];
				l=j;
			}
		}
		out[l]=tab[r];
		r++;
	}
	printf("\n");
	fclose(fp);
	fp=fopen("Encrypted.txt", "r");
	in=fgetc(fp);
	while(in!=EOF){
		in=toupper(in);
		if((int)in>=65 && (int)in<91){
			fputc(out[in-65], fp1);
		}
		else
			fputc(in, fp1);
		in=fgetc(fp);
	}
	fclose(fp);
	fclose(fp1);
}


void Caesar_encrypt(){
	FILE *fp, *fp1, *fp2;
	fp=fopen("Text.txt", "r");
	fp1=fopen("Encrypted.txt", "w");
	fp2=fopen("Key.txt", "w");
	char in, out;
	int i, n, key;
	srand(time(NULL));
	key=rand()%256;
	in=fgetc(fp);
	while(in!=EOF){
		fputc((key+(int)in)%256, fp1);
		in=fgetc(fp);
	}
	fputc(key, fp2);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}


void Caesar_decrypt(){
	FILE *fp, *fp1, *fp2;
	fp=fopen("Decrypted.txt", "w");
	fp1=fopen("Encrypted.txt", "r");
	fp2=fopen("Key.txt", "r");
	char in, out;
	int i, n, key;
	key=(int)fgetc(fp2);
	in=fgetc(fp1);
	while(in!=EOF){
		out=(int)in-key;
		if((int)in-key<0)
			out+=256;
		fputc(out,fp);
		in=fgetc(fp1);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp);
}


void Caesar_decryptNo(){
	FILE *fp, *fp1;
	fp=fopen("Decrypted.txt", "w");
	fp1=fopen("Encrypted.txt", "r");
	char in, in1;
	int a[26], i, x=0, l;
	for(i=0;i<26;i++)
		a[i]=0;
	in=fgetc(fp1);
	while(in!=EOF){
		in1=toupper(in);
		if((int)in1>=65 && (int)in1<91){
			a[(int)in1-65]++;
		}
		in=fgetc(fp1);
	}
	for(i=0;i<26;i++){
		printf("%d ", a[i]);
		if(a[i]>x){
			x=a[i];
			l=i;
		}
	}
	x=l-4;
	fclose(fp1);
	fp1=fopen("Encrypted.txt", "r");
	in=fgetc(fp1);
	while(in!=EOF){
		in=toupper(in);
		fputc(((int)in-65-x>=0? in-x:in+x), fp);
		in=fgetc(fp1);
	}
	fclose(fp1);
	fclose(fp);
}


void Vignere_encrypt(){ 
	char v_sqr[26][26];
	char temp[26]=					{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i,j;
	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			v_sqr[i][j]=temp[(j+i)%26];
		}
	}
	FILE *fin, *fout,*fkey;
	fkey=fopen("Key.txt","w");
	fout=fopen("Encrypted.txt","w");
	fin = fopen("Text.txt","r");
	int n;
	printf("Enter the length of the keyword: ");
	scanf("%d",&n);
	char keyword[n];
	int g;
	srand(time(NULL));
	for (g=0;g<n;g++){
		int r=rand()%26;
		keyword[g]=temp[r];
		fprintf(fkey,"%c",keyword[g]);
	}
	if (fin){
		char str[1024];
   		while (fscanf(fin, "%s", str) != EOF){
			int x,y,z,i;
			for(i=0;i<strlen(str);i++)
				str[i]=toupper(str[i]);
			char h[strlen(str)];
			for (x=0; x<strlen(str); x++){
				if(str[x]=='\0'){
					break;
				}
				else{
					y=(int)str[x];
					z=(int)keyword[x % n];
					h[x]=v_sqr[y-65][z-65];
				}
			}
			for(i=0;h[i]!='\0';i++){
				fputc(h[i], fout);
			}
		}
	}
	else{
		printf("No data found to encrypt");
	}
	fclose(fin);
	fclose(fout);
	fclose(fkey);
}


void Vignere_decrypt(){
	char v_sqr[26][26];
	char temp[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i,j;
	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			v_sqr[i][j]=temp[(j+i)%26];
		}
	}
	
	FILE *fin, *fout,*fkey;
	fin = fopen("Encrypted.txt","r");
	fout = fopen("Decrypted.txt","w");
	fkey = fopen("Key.txt","r");

	char keyword[1024];
	fscanf(fkey,"%s",keyword);
	if (fin){
		char str[1024];
   		while (fscanf(fin, "%s", str) != EOF){
			int x,y,z;
			char h[strlen(str)];
			for (x=0;x<strlen(str);x++){
				for (z=0;z<26;z++){
					y=(int)keyword[x % strlen(keyword)];
					if (v_sqr[y-65][z] == str[x]){
						h[x]=v_sqr[0][z];
					}
				}
			}
			fprintf(fout,"%s",h);
		}
	}
}


int main(){
	//Sub_encrypt();
	int x=1, x1, x2;
	char ch;
	printf("Enter \n1 : Encryption\n2 : Decryption (if you have key)\n3 : Decryption (if you don't have key)\n4 : Instructions\n");
	scanf("%d", &x);
	switch(x){
		case(1):{
			printf("Enter\n1 : Substitution\n2 : Caesar\n3 : Vernam\n4 : Vigenere\n");
			scanf("%d", &x1);
			if(x1){
				printf("Enter the text to be encrypted to 'Text.txt' file. Press 1 when done : ");
				scanf("%d", &x2);
				if(x2){
					if(x1==1){
						Sub_encrypt();
						scanf("%c", &ch);
						printf("Your file has been successfully encrypted. Check 'Key.txt' for the key and 'Encrypted.txt' for the encrypted file");
						break;
					}
					else if(x1==2){
						Caesar_encrypt();
						printf("Your file has been successfully encrypted. Check 'Key.txt' for the key and 'Encrypted.txt' for the encrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==3){
						vernam_encrypt();
						printf("Your file has been successfully encrypted. Check 'Encrypted.txt' for the encrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==4){
						Vignere_encrypt();
						printf("Your file has been successfully encrypted. Check 'Key.txt' for the key and 'Encrypted.txt' for the encrypted file");
						scanf("%c", &ch);
						break;
					}
					else{
						printf("Invalid Input!!!");
					}
				}
			}
			break;
		}
		case(2):{
			printf("Enter\n1 : Substitution\n2 : Caesar\n3 : Vernam\n4 : Vigenere\n");
			scanf("%d", &x1);
			if(x1){
				printf("Enter the text to be decrypted to 'Encrypted.txt' file and the key to 'Key.txt' file. Press 1 when done : ");
				scanf("%d", &x2);
				if(x2){
					if(x1==1){
						Sub_decryptkey();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==2){
						Caesar_decrypt();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==3){
						vernam_decrypt();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==4){
						Vignere_decrypt();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else{
						printf("Invalid Input!!!");
					}
				}
			}
			break;
		}
		case(3):{
			printf("Enter\n1 : Substitution\n2 : Caesar\n");
			scanf("%d", &x1);
			if(x1){
				printf("Enter the text to be decrypted to 'Encrypted.txt' file. Press 1 when done : ");
				scanf("%d", &x2);
				if(x2){
					if(x1==1){
						DecryptNo();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else if(x1==2){
						Caesar_decryptNo();
						printf("Your file has been successfully decrypted. Check 'Decrypted.txt' for the decrypted file");
						scanf("%c", &ch);
						break;
					}
					else{
						printf("Invalid Input!!!");
					}
				}
			}
		}
		case(4):{
			FILE *f1;
			f1=fopen("Instructions.txt", "r");
			char in;
			in=fgetc(f1);
			while(in!=EOF){
				printf("%c", in);
				in=fgetc(f1);
			}
			fclose(f1);
			break;
		}
	}
}
