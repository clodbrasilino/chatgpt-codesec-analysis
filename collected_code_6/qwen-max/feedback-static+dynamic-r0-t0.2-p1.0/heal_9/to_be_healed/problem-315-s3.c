#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *sentence, char *result, size_t result_size) {
    const char *word = sentence;
    int max_length = 0;
    
    while (*sentence) {
        if (*sentence == ' ' || *(sentence) == '\t' || *sentence == '\n' || *sentence == '\r' || *sentence == '\f' || *sentence == '\v') {
            size_t length = (size_t)(sentence - word);
            if (length % 2 == 0 && length > max_length && length < result_size - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, word, length);
                result[length] = '\0';
                max_length = (int)length;
            }
            word = sentence + 1;
        }
        sentence++;
    }
    
    if (*word) {
        size_t length = (size_t)(sentence - word);
        if (length % 2 == 0 && length > max_length && length < result_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, word, length);
            result[length] = '\0';
            max_length = (int)length;
        }
    }
    
    return max_length;
}

int main() {
    const char *sentence = "This is a test sentence with even and odd words";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[50];
    int max_length = findFirstMaxLengthEvenWord(sentence, result, sizeof(result));
    if (max_length > 0) {
        printf("First maximum length even word: %s\n", result);
    } else {
        printf("No even length word found.\n");
    }
    return 0;
}