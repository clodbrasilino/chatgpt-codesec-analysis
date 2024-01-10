#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void findWordsStartingWithAE(char* str) {
    char* wordStart = NULL;
    bool insideWord = false;

    /* Possible weaknesses found:
     *  Cannot determine that '*str' is initialized [premium-bughuntingUninit]
     */
    while (*str != '\0') {
        if (isspace(*str)) {
            insideWord = false;
        } else {
            if (!insideWord) {
                if (*str == 'a' || *str == 'e' || *str == 'A' || *str == 'E') {
                    wordStart = str;
                    insideWord = true;
                }
            }
        }

        if (!insideWord && wordStart != NULL) {
            printf("%.*s\n", (int)(str - wordStart), wordStart);
            wordStart = NULL;
            insideWord = false;
        }

        str++;
    }

    if (insideWord && wordStart != NULL) {
        printf("%.*s\n", (int)(str - wordStart), wordStart);
    }
}

int main() {
    char str[] = "All apples and elephants have ears.";
    findWordsStartingWithAE(str);
    return 0;
}