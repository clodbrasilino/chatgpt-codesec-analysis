#include <stdio.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (count[c] > 1) {
            return (int)c;
        }
    }

    return -2;
}

int main(void) {
    const char *tests[] = {"hello", "abcdef", "swiss", "", NULL};

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        int res = find_first_repeated(tests[i]);
        printf("Test %zu: %c\n", i + 1, res >= 0 ? res : '-');
    }

    return 0;
}