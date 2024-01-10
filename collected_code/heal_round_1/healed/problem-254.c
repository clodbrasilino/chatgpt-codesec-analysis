#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void findWordsStartingWithAE(char* str) {
    if(str == NULL) {
        return;
    }

    char* wordStart = NULL;
    bool insideWord = false;

    while (*str != '\0') {
        if (isspace(*str)) {
            if(insideWord && wordStart != NULL) {
                printf("%.*s\n", (int)(str - wordStart), wordStart);
                wordStart = NULL;
            }
            insideWord = false;
        } else {
            if (!insideWord) {
                if (*str == 'a' || *str == 'e' || *str == 'A' || *str == 'E') {
                    wordStart = str;
                }
            }
            insideWord = true;
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