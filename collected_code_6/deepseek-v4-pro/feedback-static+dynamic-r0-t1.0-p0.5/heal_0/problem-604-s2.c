#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char input[] = "Hello world from C";
    printf("Original: %s\n", input);
    reverse_words(input);
    printf("Reversed: %s\n", input);

    char empty[] = "";
    reverse_words(empty);
    printf("Empty: '%s'\n", empty);

    char single[] = "single";
    reverse_words(single);
    printf("Single: %s\n", single);

    char multiple_spaces[] = "  multiple   spaces  ";
    reverse_words(multiple_spaces);
    printf("Multiple spaces: '%s'\n", multiple_spaces);

    return 0;
}