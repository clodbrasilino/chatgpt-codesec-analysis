#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_range(char *start, char *end) {
    char temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *word_start = str;
    char *p = str;

    while (*p != '\0') {
        if (*p == ' ') {
            if (word_start < p) {
                reverse_range(word_start, p - 1);
            }
            word_start = p + 1;
        }
        p++;
    }

    if (word_start < p) {
        reverse_range(word_start, p - 1);
    }

    return str;
}

int main(void) {
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    reverse_words(input);
    printf("Reversed words: %s\n", input);

    return 0;
}