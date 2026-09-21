#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t bufsiz, size_t k) {
    if (str == NULL || bufsiz == 0) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (read_idx < bufsiz && str[read_idx] != '\0') {
        if (isalpha((unsigned char)str[read_idx])) {
            size_t start_idx = read_idx;
            size_t length = 0;

            while (read_idx < bufsiz && str[read_idx] != '\0' && isalpha((unsigned char)str[read_idx])) {
                length++;
                read_idx++;
            }

            if (length != k) {
                for (size_t i = 0; i < length; i++) {
                    if (write_idx < bufsiz - 1) {
                        str[write_idx++] = str[start_idx + i];
                    }
                }
            }
        } else {
            if (write_idx < bufsiz - 1) {
                str[write_idx++] = str[read_idx];
            }
            read_idx++;
        }
    }

    str[write_idx] = '\0';
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    printf("Before: %s\n", text);
    remove_words_of_length(text, sizeof(text), k);
    printf("After: %s\n", text);

    return 0;
}