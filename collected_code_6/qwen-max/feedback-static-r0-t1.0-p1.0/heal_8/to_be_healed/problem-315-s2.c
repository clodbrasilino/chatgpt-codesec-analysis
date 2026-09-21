#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *sentence, char *word, size_t word_size) {
    int max_length = 0;
    const char *p = sentence;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') {
            p++;
        }
        int len = p - start;
        if (len % 2 == 0 && len > max_length) {
            if (len + 1 <= (int)word_size) {
                max_length = len;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, start, len);
                word[len] = '\0';
            }
        }
        if (*p) {
            p++;
        }
    }
    return max_length;
}

int main() {
    const char *sentence = "This is a test sentence with even and odd length words";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[100];
    int length = findFirstMaxLengthEvenWord(sentence, word, sizeof(word) - 1);
    if (length > 0) {
        printf("The first maximum length even word is: '%s' with length %d\n", word, length);
    } else {
        printf("No even length word found.\n");
    }
    return 0;
}