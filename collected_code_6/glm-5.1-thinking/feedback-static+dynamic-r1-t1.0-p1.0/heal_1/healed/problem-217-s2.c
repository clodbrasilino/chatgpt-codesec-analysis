#include <stdio.h>

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};

    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (seen[c] == 1) {
            return *str;
        }
        seen[c] = 1;
        str++;
    }

    return '\0';
}

int main(void) {
    const char *test1 = "programming";
    const char *test2 = "abcdef";
    const char *test3 = "aabb";

    char result;

    result = find_first_repeated(test1);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    result = find_first_repeated(test2);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    result = find_first_repeated(test3);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}