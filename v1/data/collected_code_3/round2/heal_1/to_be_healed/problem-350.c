#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

char str[1000], ch;
int i, j, count[26] = {0}, min;

void minimize_string() {
    for(i = 0; str[i] != '\0'; i++) {
        count[str[i] - 'a']++;
    }

    min = count[0];
    ch = 'a';

    for(i = 1; i < 26; i++) {
        if(count[i] < min) {
            min = count[i];
            ch = i + 'a';
        }
    }

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] != ch) {
            printf("%c", str[i]);
        }
    }
}

int main() {
    printf("Enter a string: ");
    gets(str);

    for(i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
         */
        str[i] = tolower(str[i]);
    }

    minimize_string();

    return 0;
}