#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_reverse(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    size_t i;

    if (a == NULL || b == NULL) {
        return 0;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    if (len_a != len_b) {
        return 0;
    }

    for (i = 0; i < len_a; i++) {
        if (a[i] != b[len_a - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

size_t count_reverse_pairs(const char **strings, size_t count)
{
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (strings == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse(strings[i], strings[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *list[] = {"abc", "cba", "hello", "olleh", "world", "abc"};
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t result;

    result = count_reverse_pairs(list, count);

    if (printf("Number of reverse pairs: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}