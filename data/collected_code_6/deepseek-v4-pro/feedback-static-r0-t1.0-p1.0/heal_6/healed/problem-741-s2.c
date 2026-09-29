#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int all_chars_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 1;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t length;

    printf("Enter a string: ");
    length = getline(&input, &bufsize, stdin);
    
    if (length == -1) {
        free(input);
        return 1;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
        length--;
    }

    if (all_chars_same(input)) {
        printf("All characters are the same.\n");
    } else {
        printf("Characters are not all the same.\n");
    }

    free(input);
    return 0;
}