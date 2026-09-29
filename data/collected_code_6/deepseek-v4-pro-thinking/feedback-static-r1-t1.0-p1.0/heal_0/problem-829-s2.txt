#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int cmpstr(const void *a, const void *b)
{
    const char *const *pa = a;
    const char *const *pb = b;
    return strcmp(*pa, *pb);
}

char *second_most_repeated(char *strings[], size_t n)
{
    if (strings == NULL || n == 0) {
        return NULL;
    }
    if (n > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **sorted = malloc(n * sizeof(char *));
    if (sorted == NULL) {
        return NULL;
    }

    memcpy(sorted, strings, n * sizeof(char *));
    qsort(sorted, n, sizeof(char *), cmpstr);

    char *first = NULL;
    char *second = NULL;
    size_t first_count = 0;
    size_t second_count = 0;

    size_t i = 0;
    while (i < n) {
        char *current = sorted[i];
        size_t j = i + 1;
        while (j < n && strcmp(sorted[j], current) == 0) {
            j++;
        }
        size_t count = j - i;

        if (count > first_count) {
            second = first;
            second_count = first_count;
            first = current;
            first_count = count;
        } else if (count > second_count && count < first_count) {
            second = current;
            second_count = count;
        }

        i = j;
    }

    free(sorted);
    return second;
}

int main(void)
{
    char *sequence[] = {"aaa", "bbb", "aaa", "ccc", "bbb", "aaa"};
    size_t n = sizeof(sequence) / sizeof(sequence[0]);
    char *result = second_most_repeated(sequence, n);

    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("No second most repeated string\n");
    }

    return 0;
}