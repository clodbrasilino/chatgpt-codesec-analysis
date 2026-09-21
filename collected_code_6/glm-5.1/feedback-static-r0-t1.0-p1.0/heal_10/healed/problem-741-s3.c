#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return true;
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
    char *input = NULL;
    size_t buffer_size = 0;

    if (getline(&input, &buffer_size, stdin) != -1) {
        size_t len = strcspn(input, "\n");
        input[len] = '\0';

        if (are_all_chars_same(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    free(input);
    return 0;
}