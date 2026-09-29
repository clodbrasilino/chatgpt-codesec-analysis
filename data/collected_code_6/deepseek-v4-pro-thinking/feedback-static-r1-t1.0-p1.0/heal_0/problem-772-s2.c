#include <ctype.h>
#include <stdio.h>

void remove_words_of_length(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    int first_kept = 1;

    while (*read != '\0') {
        while (*read != '\0' && isspace((unsigned char)*read)) {
            read++;
        }

        if (*read == '\0') {
            break;
        }

        char *word_start = read;

        while (*read != '\0' && !isspace((unsigned char)*read)) {
            read++;
        }

        int word_length = (int)(read - word_start);

        if (word_length != k) {
            if (!first_kept) {
                *write++ = ' ';
            }

            while (word_start < read) {
                *write++ = *word_start++;
            }

            first_kept = 0;
        }
    }

    *write = '\0';
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, 2);
    printf("%s\n", text);
    return 0;
}