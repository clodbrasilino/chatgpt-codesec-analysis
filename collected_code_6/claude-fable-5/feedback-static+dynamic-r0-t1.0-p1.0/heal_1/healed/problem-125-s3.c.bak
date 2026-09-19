#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max_difference(const char *str)
{
    size_t len;
    size_t i;
    int current;
    int best;
    int value;

    if (str == NULL) {
        return -1;
    }

    len = strlen(str);
    if (len == 0) {
        return -1;
    }

    current = 0;
    best = -1;

    for (i = 0; i < len; i++) {
        if (str[i] == '0') {
            value = 1;
        } else if (str[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        current += value;
        if (current < value) {
            current = value;
        }
        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main(void)
{
    const char *tests[] = {
        "11000010001",
        "1111",
        "0000",
        "101010"
    };
    size_t count;
    size_t i;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        int result = find_max_difference(tests[i]);
        if (result < 0) {
            if (printf("String: %s -> no valid substring with more 0s than 1s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("String: %s -> max difference: %d\n", tests[i], result) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}