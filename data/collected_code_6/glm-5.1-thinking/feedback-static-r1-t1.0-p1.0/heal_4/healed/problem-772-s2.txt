#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t bufsiz, size_t k) {
    if (str == NULL || bufsiz == 0) {
        return;
    }

    const char *read = str;
    char *write = str;
    const char *end = str + bufsiz;

    while (read < end && *read != '\0') {
        if (isalpha((unsigned char)*read)) {
            const char *start = read;
            size_t length = 0;

            while (read < end && *read != '\0' && isalpha((unsigned char)*read)) {
                length++;
                read++;
            }

            if (length != k) {
                for (size_t i = 0; i < length; i++) {
                    if (write < end - 1) {
                        *write++ = start[i];
                    }
                }
            }
        } else {
            if (write < end - 1) {
                *write++ = *read;
            }
            read++;
        }
    }

    if (write < end) {
        *write = '\0';
    }
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    printf("Before: %s\n", text);
    remove_words_of_length(text, sizeof(text), k);
    printf("After: %s\n", text);

    return 0;
}