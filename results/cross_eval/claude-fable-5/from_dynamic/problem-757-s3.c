#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_reverse(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    size_t i;

    if ((a == NULL) || (b == NULL)) {
        return false;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    if (len_a != len_b) {
        return false;
    }

    for (i = 0; i < len_a; i++) {
        if (a[i] != b[len_a - 1U - i]) {
            return false;
        }
    }

    return true;
}

static size_t count_reverse_pairs(const char *const *strings, size_t count)
{
    size_t pairs = 0U;
    size_t i;
    size_t j;

    if (strings == NULL) {
        return 0U;
    }

    for (i = 0U; i < count; i++) {
        for (j = i + 1U; j < count; j++) {
            if (is_reverse(strings[i], strings[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *const test_list[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "world",
        "abc"
    };
    size_t list_size = sizeof(test_list) / sizeof(test_list[0]);
    size_t result;

    result = count_reverse_pairs(test_list, list_size);

    if (printf("Number of reverse string pairs: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}