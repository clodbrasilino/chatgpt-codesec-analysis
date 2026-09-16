#include <stdio.h>
#include <string.h>

static void reverse_range(char *begin, char *end) {
    while (begin < end) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
        end--;
    }
}

void reverse_words(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len < 2) {
        return;
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
}

int main(void) {
    char str[] = "Hello world from C";

    printf("Original: %s\n", str);
    reverse_words(str);
    printf("Reversed: %s\n", str);

    return 0;
}