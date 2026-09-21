#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

char *remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 0) {
        return str;
    }

    size_t read = 0;
    size_t write = 0;
    size_t target_len = (size_t)k;

    while (read < size && str[read] != '\0') {
        if (isspace((unsigned char)str[read])) {
            if (write < size) {
                str[write++] = str[read];
            }
            read++;
        } else {
            size_t word_start = read;
            while (read < size && str[read] != '\0' && !isspace((unsigned char)str[read])) {
                read++;
            }

            size_t word_len = read - word_start;

            if (word_len != target_len) {
                for (size_t i = 0; i < word_len; ++i) {
                    if (write < size) {
                        str[write++] = str[word_start + i];
                    }
                }
            }
        }
    }

    if (write < size) {
        str[write] = '\0';
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