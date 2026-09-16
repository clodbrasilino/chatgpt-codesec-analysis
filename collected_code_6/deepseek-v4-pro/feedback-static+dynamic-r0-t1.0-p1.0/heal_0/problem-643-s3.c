#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool match_word_with_internal_z(const char *text) {
    if (text == NULL) {
        return false;
    }

    const char *word_start = text;
    const char *p = text;

    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            size_t len = (size_t)(p - word_start);
            if (len > 2) {
                const char *q = word_start + 1;
                const char *q_end = p - 1;
                for (; q < q_end; q++) {
                    if (*q == 'z' || *q == 'Z') {
                        return true;
                    }
                }
            }
            word_start = p + 1;
        }
        p++;
    }

    size_t len = (size_t)(p - word_start);
    if (len > 2) {
        const char *q = word_start + 1;
        const char *q_end = p - 1;
        for (; q < q_end; q++) {
            if (*q == 'z' || *q == 'Z') {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    char input[1024];

    printf("Enter text: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (match_word_with_internal_z(input)) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}