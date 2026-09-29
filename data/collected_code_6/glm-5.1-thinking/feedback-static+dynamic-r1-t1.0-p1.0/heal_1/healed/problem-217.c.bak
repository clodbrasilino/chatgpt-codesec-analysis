#include <stdio.h>
#include <string.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int char_set[256] = {0};
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] > 0) {
            return (int)c;
        }
        char_set[c]++;
    }

    return -1;
}

int main(void) {
    const char *tests[] = {"programming", "abcdef", "abba", NULL};
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int res = find_first_repeated(tests[i]);
        if (res != -1) {
            printf("%c\n", res);
        } else {
            printf("No repeated character\n");
        }
    }

    return 0;
}