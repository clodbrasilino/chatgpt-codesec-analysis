#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

char *remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 0) {
        return str;
    }

    char *read = str;
    char *write = str;
    char *end = str + size;

    while (read < end && *read != '\0') {
        while (read < end && *read != '\0' && isspace((unsigned char)*read)) {
            *write++ = *read++;
        }

        if (read >= end || *read == '\0') {
            break;
        }

        char *word_start = read;
        while (read < end && *read != '\0' && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != (size_t)k) {
            while (word_start < read) {
                *write++ = *word_start++;
            }
        }
    }

    if (write < end) {
        *write = '\0';
    } else {
        *(end - 1) = '\0';
    }

    return str;
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: %s\n", str1);
    remove_words_of_length(str1, sizeof(str1), 4);
    printf("Modified: %s\n", str1);

    char str2[] = "Hello \t world \n from C programming";
    printf("Original: %s\n", str2);
    remove_words_of_length(str2, sizeof(str2), 5);
    printf("Modified: %s\n", str2);

    return 0;
}