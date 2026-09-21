#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void reverse_range(char *start, char *end) {
    while (start < end) {
        char temp = *start;
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

    size_t len = strnlen(str, 255);
    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *word_start = str;
    char *p = str;

    while (*p != '\0') {
        if (*p == ' ') {
            reverse_range(word_start, p - 1);
            word_start = p + 1;
        }
        p++;
    }

    reverse_range(word_start, p - 1);

    return str;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;

    printf("Enter a string: ");

    ssize_t nread = getline(&input, &bufsize, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
        nread--;
    }

    if (nread > 255) {
        input[255] = '\0';
    }

    reverse_words(input);
    printf("Reversed words: %s\n", input);

    free(input);
    return 0;
}