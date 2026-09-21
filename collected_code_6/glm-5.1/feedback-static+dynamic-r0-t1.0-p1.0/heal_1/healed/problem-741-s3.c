#include <stdio.h>
#include <stdbool.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return true;
    }

    char first = str[0];
    size_t i = 1;

    while (str[i] != '\0') {
        if (str[i] != first) {
            return false;
        }
        i++;
    }

    return true;
}

int main(void) {
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t i = 0;
        while (i < sizeof(input) && input[i] != '\0') {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
            i++;
        }

        if (are_all_chars_same(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}