#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

bool all_chars_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return false;
        }
    }
    return true;
}

int main(void) {
    char input[256];
    int c;
    size_t i = 0;
    bool truncated = false;

    printf("Enter a string: ");

    while (i < sizeof(input) - 1) {
        c = getchar();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            break;
        }
        input[i] = (char)c;
        i++;
    }

    if (i == sizeof(input) - 1 && c != '\n' && c != EOF) {
        truncated = true;
        int discard;
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
    }

    input[i] = '\0';

    if (i == 0 && c == EOF) {
        return 1;
    }

    if (truncated) {
        printf("False\n");
        return 0;
    }

    if (all_chars_same(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}