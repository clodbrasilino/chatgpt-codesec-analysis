#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *sentence, char *result) {
    const char *word = sentence;
    int max_length = 0;
    while (*sentence) {
        if (*sentence == ' ') {
            int length = sentence - word;
            if (length % 2 == 0 && length > max_length) {
                max_length = length;
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result, word, length);
                result[length] = '\0';
            }
            word = sentence + 1;
        }
        sentence++;
    }
    int length = sentence - word;
    if (length % 2 == 0 && length > max_length) {
        max_length = length;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result, word, length);
        result[length] = '\0';
    }
    return max_length;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'sentence' can be declared as const array [constVariable]
     */
    char sentence[] = "This is a test sentence with even and odd words";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[50];
    int max_length = findFirstMaxLengthEvenWord(sentence, result);
    if (max_length > 0) {
        printf("First maximum length even word: %s\n", result);
    } else {
        printf("No even length word found.\n");
    }
    return 0;
}