
#include "functions.h"

// remove duplicate characters in array word and return the resulting string
char * removeDuplicates(char word[]){
	char * answer;
	int len = sizeof(word);
	answer = (char	*) malloc (len * sizeof(char));
	char letter;
	int a = 0;
	int b = 0;


	while (a < len){

		letter = word[a];

		//makes next character null for end of string
		answer[a+1] = '\a';

		if(targetFound(answer,a,letter) == 0){
			answer[b] = letter;
			b++;
		}
		a++;	
	}

	answer[sizeof(answer)] = '\0';
	return answer;
}

// search the first num characters in array charArray for character target
// return a non-zero integer if found, otherwise, return 0
int targetFound(char charArray[], int num, char target){

	int a = 0;
	while (a < sizeof(charArray)){
		if (target == charArray[a]){
			return 1;
		}
		a++;
	}
	return 0;
}

// initialize the encrypt array with appropriate cipher letters according to the given key
void initializeEncryptArray(char key[], char encrypt[]){
	char abc[] = {'Z','Y','X','W','V','U','T','S','R','Q','P','O','N','M','L','K','J','I','H','G','F','E','D','C','B','A'};
	
	encrypt[sizeof(encrypt)] = '\0';

	int j = 0;
	int size = 0;

	//adding key to encrypt array and will terminate when it reaches null
	//character (end of string)
	while (key[j] != '\0'){
		encrypt[j] = key[j];
			size++;
		j++;

	}

	char ch;
	int i = 0;
	j = size;
	while (j < 26){

		ch = abc[i];

		if (targetFound(encrypt, sizeof(encrypt), ch) == 0){
			encrypt[j] = ch;
			j++;
		}
		i++;
	}

	encrypt[26] = '\0';
	

}

// initialize decrypt array with appropriate substitute letters based on the encrypt array
void initializeDecryptArray(char encrypt[], char decrypt[]){
	int k = 0;
	char alpha[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	while (k < 26){
		decrypt[encrypt[k]-'A'] = alpha[k];
		k++;

	}

	decrypt[26] = '\0';
}

// process data from the input file and write the result to the output file
// pass the encrypt array to parameter substitute if encryption is intended
// pass the decrypt array to parameter substitute if decryption is intended
void processInput(FILE * inf, FILE * outf, char encrypt[]){
	char ch;
	while ( fscanf(inf, "%c", &ch) != EOF ){

		if(isupper(ch)){
			fprintf(outf, "%c", encrypt[ch - 'A']);
		}

		else{
			fprintf(outf, "%c", ch);
		}
	}
}