#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

char *remove_words_of_length(char *str, int k) {
    if (str == NULL || k < 0) {
        return str;
    }

    char *read = str;
    char *write = str;
    char *end = str + strlen(str);

    while (read < end) {
        while (read < end && isspace((unsigned char)*read)) {
            *write++ = *read++;
        }

        if (read >= end) {
            break;
        }

        char *word_start = read;
        while (read < end && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != (size_t)k) {
            while (word_start < read) {
                *write++ = *word_start++;
            }
        }
    }

    *write = '\0';
    return str;
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: %s\n", str1);
    remove_words_of_length(str1, 4);
    printf("Modified: %s\n", str1);

    char str2[] = "Hello \t world \n from C programming";
    printf("Original: %s\n", str2);
    remove_words_of_length(str2, 5);
    printf("Modified: %s\n", str2);

    return 0;
}