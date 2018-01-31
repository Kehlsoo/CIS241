#include <stdio.h>
#include <ctype.h>
int main () {
        puts ("Enter text (ctrl-D to quit).");
        while (ch = getchar(), ch != EOF ) {
                if (islower(ch)){
                        ch = toupper(ch);
                }
                else {
                        ch = tolower(ch);
                }
                putchar(ch);
        }
        return 0;
}