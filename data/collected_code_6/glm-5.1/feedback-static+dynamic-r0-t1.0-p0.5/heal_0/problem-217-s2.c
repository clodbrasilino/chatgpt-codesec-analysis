#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int *char_set = (int *)calloc(256, sizeof(int));
    if (char_set == NULL) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            free(char_set);
            return str[i];
        }
        char_set[c] = 1;
    }

    free(char_set);
    return '\0';
}

int main(void) {
    const char *test_str = "programming";
    char result = find_first_repeated(test_str);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated characters found.\n");
    }

    return 0;
}