#include <stdio.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int seen[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] == 1) {
            return (int)c;
        }
        seen[c] = 1;
    }

    return -1;
}

int main(void) {
    const char *tests[] = {"programming", "abcdef", NULL};
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int result = find_first_repeated(tests[i]);
        if (result != -1) {
            printf("%c\n", result);
        } else {
            printf("No repeated character\n");
        }
    }

    return 0;
}