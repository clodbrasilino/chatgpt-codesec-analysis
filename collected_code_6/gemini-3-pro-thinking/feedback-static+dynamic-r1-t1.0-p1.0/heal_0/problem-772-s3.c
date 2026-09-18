#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_k_length_words(char *str, size_t k);

void remove_k_length_words(char *str, size_t k) {
    if (str == NULL) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;
    int is_first_word = 1;

    while (str[read_idx] != '\0') {
        while (str[read_idx] != '\0' && isspace((unsigned char)str[read_idx])) {
            read_idx++;
        }

        if (str[read_idx] == '\0') {
            break;
        }

        size_t word_start = read_idx;
        size_t word_len = 0;

        while (str[read_idx] != '\0' && !isspace((unsigned char)str[read_idx])) {
            word_len++;
            read_idx++;
        }

        if (word_len != k) {
            if (!is_first_word) {
                str[write_idx++] = ' ';
            }
            for (size_t i = 0; i < word_len; i++) {
                str[write_idx++] = str[word_start + i];
            }
            is_first_word = 0;
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str1[] = "The quick brown fox jumps over the lazy dog";
    char str2[] = "Hello world this is a test string";
    char str3[] = "   Spaces   should   be   handled properly   ";

    remove_k_length_words(str1, 5);
    printf("%s\n", str1);

    remove_k_length_words(str2, 2);
    printf("%s\n", str2);

    remove_k_length_words(str3, 6);
    printf("%s\n", str3);

    remove_k_length_words(NULL, 4);

    return 0;
}