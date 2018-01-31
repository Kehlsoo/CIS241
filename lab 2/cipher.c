#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char ch, int k);

int main(int argc, char* argv[]){
	int choice, key;
	char ch;
	char * str;
	FILE *fin, *fout;

	if (argc != 5){
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption");
		exit(1);
	}

	choice = atoi(argv[1]);
	str = argv[2];

	int len = strlen(str);

	int * key_arr = (int*)malloc(len*sizeof(int));

	 int j = 0;
        while (j<len){
                key = (toupper(str[j]) - 'A');

                if (choice == 2){
                        key = -key;
                }

                key_arr[j] = key;
                j++;
        }


	fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");

	if (fin ==  NULL || fout == NULL) {
		printf("File could not be opened\n");
		exit(1);
	}

	int i = 0;
	while (fscanf(fin, "%c", &ch) != EOF){
		int move = key_arr[i % len];
		fprintf(fout, "%c", encrypt(ch, move));
		i++;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}

char encrypt(char ch, int k){
	if ( k < 0 )
		k = k + 26;

	if ( isupper(ch) )
		return (ch - 'A' + k) % 26 + 'A';

	if ( islower(ch) )
		return (ch - 'a' + k) % 26 + 'a';

	return ch;
}