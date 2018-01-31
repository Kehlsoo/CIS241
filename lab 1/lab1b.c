#include <stdio.h>
#include <ctype.h>
int main () {
        char ch;
        int alphCount = 0;
        int symCount = 0;
        int wordCount = 0;
        int symWord = 0;
        puts ("Enter text (ctrl-D to quit).");
        while (ch = getchar(), ch != EOF ) {
                if (isalnum(ch)){
                        alphCount += 1;
                }
                else if (ispunct(ch)){
                        symCount += 1;
                }
                else if (isspace(ch)){
                        if (symCount > 0){
                                symWord += 1;
                        }
                        if (alphCount > 0){
                                wordCount += 1;
                        }
                }
        }
        printf("Symbol Sequence: %d\n", symWord);
        printf("Word Sequence: %d\n", wordCount);
        return 0;
}