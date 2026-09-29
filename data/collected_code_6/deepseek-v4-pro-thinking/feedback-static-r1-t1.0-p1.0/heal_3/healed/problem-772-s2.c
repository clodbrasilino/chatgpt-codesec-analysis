#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k <= 0) {
        return;
    }

    size_t i = 0, j = 0;
    int first_kept = 1;

    while (i < size && str[i] != '\0') {
        while (i < size && str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= size || str[i] == '\0') {
            break;
        }

        size_t word_start = i;
        while (i < size && str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }

        size_t word_length = i - word_start;

        if ((int)word_length != k) {
            if (!first_kept) {
                if (j < size) {
                    str[j++] = ' ';
                }
            }

            while (word_start < i && j < size) {
                str[j++] = str[word_start++];
            }

            first_kept = 0;
        }
    }

    if (j < size) {
        str[j] = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, sizeof(text), 2);
    printf("%s\n", text);
    return 0;
}