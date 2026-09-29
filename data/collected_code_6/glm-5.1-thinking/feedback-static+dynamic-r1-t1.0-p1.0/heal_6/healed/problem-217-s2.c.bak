#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef EINVAL
#define EINVAL 22
#endif

int find_first_repeated(const char *str) {
    if (str == NULL) {
        errno = EINVAL;
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
        errno = 0;
        int result = find_first_repeated(tests[i]);
        if (result != -1) {
            printf("%c\n", (char)result);
        } else if (errno != 0) {
            printf("Invalid input\n");
        } else {
            printf("No repeated character\n");
        }
    }

    return 0;
}