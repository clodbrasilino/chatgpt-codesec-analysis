#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DICT_MAX_LEN 4096

int dict_depth(const char *dict, int *depth)
{
    size_t i;
    size_t len;
    int current;
    int max;

    if (dict == NULL || depth == NULL) {
        return -1;
    }

    len = strnlen(dict, DICT_MAX_LEN);
    if (len == DICT_MAX_LEN && dict[DICT_MAX_LEN - 1] != '\0') {
        return -1;
    }

    current = 0;
    max = 0;

    for (i = 0; i < len; i++) {
        if (dict[i] == '{') {
            if (current == INT_MAX) {
                return -1;
            }
            current++;
            if (current > max) {
                max = current;
            }
        } else if (dict[i] == '}') {
            if (current <= 0) {
                return -1;
            }
            current--;
        }
    }

    if (current != 0) {
        return -1;
    }

    *depth = max;
    return 0;
}

int main(void)
{
    const char *tests[] = {
        "{'a': 1, 'b': 2}",
        "{'a': {'b': {'c': 3}}}",
        "{'a': {'b': 1}, 'c': {'d': {'e': {'f': 4}}}}",
        "{}",
        "{'a': {'b': 1}"
    };
    size_t count;
    size_t i;
    int depth;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        int status;

        depth = 0;
        status = dict_depth(tests[i], &depth);
        if (status == 0) {
            if (printf("Dictionary: %s -> Depth: %d\n", tests[i], depth) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Dictionary: %s -> Invalid or malformed input\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}