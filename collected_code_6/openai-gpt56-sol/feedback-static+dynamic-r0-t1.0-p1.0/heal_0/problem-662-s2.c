#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_strings(const void *left, const void *right)
{
    const char *const *a = left;
    const char *const *b = right;

    return strcmp(*a, *b);
}

static void sort_dictionary(char *entries[], size_t count)
{
    if (entries == NULL || count < 2U) {
        return;
    }

    qsort(entries, count, sizeof(*entries), compare_strings);
}

int main(void)
{
    char *dictionary[] = {
        "orange",
        "apple",
        "grape",
        "banana",
        "cherry"
    };
    const size_t count = sizeof(dictionary) / sizeof(dictionary[0]);

    sort_dictionary(dictionary, count);

    for (size_t i = 0U; i < count; ++i) {
        if (puts(dictionary[i]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}