#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return true;
    }

    if (str[0] == '\0') {
        return true;
    }

    size_t len = strlen(str);
    for (size_t i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (are_all_chars_same(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}