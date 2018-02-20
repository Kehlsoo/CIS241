#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "functions.h"


int main(int argc, char * argv[]){

  int MAXNUM = 26;
  char * encrypt, * decrypt, *key;
  char choice;
  FILE * fin, * fout;


  choice = toupper(*argv[1]);


  key = removeDuplicates(argv[2]);

  fin = fopen(argv[3], "r");
  fout = fopen(argv[4],"w");
  
  encrypt = (char	*) malloc (MAXNUM * sizeof(char));
  
  //encrypt
  if (choice == 'E' || choice == 'e'){
    initializeEncryptArray(key, encrypt);
    processInput(fin, fout, encrypt);
  }

//decrypt
  else if (choice == 'D' || choice == 'd'){
    decrypt = (char	*)	malloc (MAXNUM * sizeof(char));
    initializeEncryptArray(key, encrypt);
    initializeDecryptArray(encrypt, decrypt);
    processInput( fin, fout, decrypt);
    free(decrypt);
  }
  
  free(encrypt);
  fclose(fin);
  fclose(fout);
}