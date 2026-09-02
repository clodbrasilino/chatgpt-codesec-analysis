#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

void countCharacterFrequency(const char *str, int *frequency) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z') {
            /* Possible weaknesses found:
             *  include the header <ctype.h> or explicitly provide a declaration for 'tolower'
             *  call to undeclared library function 'tolower' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
             */
            frequency[tolower(str[i]) - 'a']++;
        }
    }
}

int main() {
    const char *input = "Hello, World!";
    int frequency[26] = {0};

    countCharacterFrequency(input, frequency);

    for (int i = 0; i < 26; ++i) {
        if (frequency[i] > 0) {
            printf("'%c': %d\n", 'a' + i, frequency[i]);
        }
    }

    return 0;
}