#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

char *remove_words_of_length(char *str, size_t size, size_t k) {
    if (str == NULL || size == 0) {
        return str;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (read_idx < size && str[read_idx] != '\0') {
        while (read_idx < size && str[read_idx] != '\0' && isspace((unsigned char)str[read_idx])) {
            if (write_idx < size) {
                str[write_idx++] = str[read_idx];
            }
            read_idx++;
        }

        if (read_idx >= size || str[read_idx] == '\0') {
            break;
        }

        size_t word_start = read_idx;
        while (read_idx < size && str[read_idx] != '\0' && !isspace((unsigned char)str[read_idx])) {
            read_idx++;
        }

        size_t word_len = read_idx - word_start;

        if (word_len != k) {
            for (size_t i = word_start; i < read_idx; ++i) {
                if (write_idx < size) {
                    str[write_idx++] = str[i];
                }
            }
        }
    }

    if (write_idx < size) {
        str[write_idx] = '\0';
    } else {
        str[size - 1] = '\0';
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