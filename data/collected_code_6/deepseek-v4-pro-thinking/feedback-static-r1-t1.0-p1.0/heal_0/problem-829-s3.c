#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *second_most_repeated(const char **strings, size_t n)
{
    if (strings == NULL || n == 0) {
        return NULL;
    }

    typedef struct {
        const char *str;
        size_t count;
    } Entry;

    Entry *entries = malloc(n * sizeof(*entries));
    if (entries == NULL) {
        return NULL;
    }

    size_t distinct = 0;

    for (size_t i = 0; i < n; ++i) {
        const char *str = strings[i];
        if (str == NULL) {
            continue;
        }

        size_t j = 0;
        while (j < distinct && strcmp(entries[j].str, str) != 0) {
            ++j;
        }

        if (j < distinct) {
            ++entries[j].count;
        } else {
            entries[distinct].str = str;
            entries[distinct].count = 1;
            ++distinct;
        }
    }

    if (distinct < 2) {
        free(entries);
        return NULL;
    }

    size_t max_idx = 0;
    for (size_t i = 1; i < distinct; ++i) {
        if (entries[i].count > entries[max_idx].count) {
            max_idx = i;
        }
    }

    size_t second_idx = distinct;
    for (size_t i = 0; i < distinct; ++i) {
        if (i == max_idx || entries[i].count == entries[max_idx].count) {
            continue;
        }
        if (second_idx == distinct || entries[i].count > entries[second_idx].count) {
            second_idx = i;
        }
    }

    if (second_idx == distinct) {
        free(entries);
        return NULL;
    }

    const char *result = entries[second_idx].str;
    free(entries);
    return result;
}

int main(void)
{
    const char *sequence[] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "orange"
    };
    size_t n = sizeof(sequence) / sizeof(sequence[0]);

    const char *result = second_most_repeated(sequence, n);

    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("No second most repeated string\n");
    }

    return 0;
}