#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findWordsStartingWithAE(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t wordStart = 0;
    size_t wordLen = 0;
    int inWord = 0;
    size_t pos = 0;

    while (str[pos] != '\0') {
        if (isspace((unsigned char)str[pos])) {
            if (inWord && wordLen > 0) {
                char first = (char)tolower((unsigned char)str[wordStart]);
                if (first == 'a' || first == 'e') {
                    printf("%.*s\n", (int)wordLen, str + wordStart);
                }
                inWord = 0;
                wordLen = 0;
            }
        } else {
            if (!inWord) {
                wordStart = pos;
                inWord = 1;
            }
            wordLen++;
        }
        pos++;
    }

    if (inWord && wordLen > 0) {
        char first = (char)tolower((unsigned char)str[wordStart]);
        if (first == 'a' || first == 'e') {
            printf("%.*s\n", (int)wordLen, str + wordStart);
        }
    }
}

int main(void) {
    const char *input = "Apple banana elephant orange avocado egg";
    findWordsStartingWithAE(input);
    return 0;
}