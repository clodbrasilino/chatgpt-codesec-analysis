#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *sentence) {
    int maxLength = 0;
    const char *wordStart = sentence;
    while (*sentence) {
        if (*sentence == ' ') {
            int wordLength = sentence - wordStart;
            if (wordLength > maxLength && wordLength % 2 == 0) {
                maxLength = wordLength;
            }
            wordStart = sentence + 1;
        }
        ++sentence;
    }
    int wordLength = sentence - wordStart;
    if (wordLength > maxLength && wordLength % 2 == 0) {
        maxLength = wordLength;
    }
    return maxLength;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'input' can be declared as const array [constVariable]
     */
    char input[] = "This is a test of the even length words";
    int result = findFirstMaxLengthEvenWord(input);
    printf("%d\n", result);
    return 0;
}