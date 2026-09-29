#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void remove_k_length_words(char *str, size_t k) {
    if (str == NULL) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (str[read_idx] != '\0') {
        if (isspace((unsigned char)str[read_idx])) {
            str[write_idx++] = str[read_idx++];
        } else {
            size_t word_len = 0;
            
            while (str[read_idx + word_len] != '\0' && !isspace((unsigned char)str[read_idx + word_len])) {
                word_len++;
            }

            if (word_len == k) {
                read_idx += word_len;
            } else {
                for (size_t i = 0; i < word_len; i++) {
                    str[write_idx++] = str[read_idx++];
                }
            }
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char buffer[] = "This is a test string to check if words of length four are removed";
    size_t k = 4;

    remove_k_length_words(buffer, k);
    printf("%s\n", buffer);

    return 0;
}