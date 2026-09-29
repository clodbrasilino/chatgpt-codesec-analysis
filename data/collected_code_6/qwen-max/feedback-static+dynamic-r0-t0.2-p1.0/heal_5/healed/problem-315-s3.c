#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *sentence, char *result, size_t result_size) {
    const char *word = sentence;
    int max_length = 0;
    while (*sentence) {
        if (*sentence == ' ' || *sentence == '\0') {
            int length = sentence - word;
            if (length % 2 == 0 && length > max_length && length < (int)result_size - 1) {
                strncpy(result, word, length);
                result[length] = '\0';
                max_length = length;
            }
            word = sentence + 1;
        }
        sentence++;
    }
    return max_length;
}

int main() {
    const char *sentence = "This is a test sentence with even and odd words";
    char result[50];
    int max_length = findFirstMaxLengthEvenWord(sentence, result, sizeof(result));
    if (max_length > 0) {
        printf("First maximum length even word: %s\n", result);
    } else {
        printf("No even length word found.\n");
    }
    return 0;
}