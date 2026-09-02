#include <stdio.h>
#include <string.h>

int all_chars_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 1;
    }

    char first = str[0];
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (all_chars_same(input)) {
        printf("All characters are the same.\n");
    } else {
        printf("Characters are not all the same.\n");
    }

    return 0;
}