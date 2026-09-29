#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int third;
} Tuple;

int *extract_nth(const Tuple *tuples, size_t count, size_t n)
{
    int *result;
    size_t i;

    if (tuples == NULL || count == 0 || n > 2U) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        switch (n) {
        case 0:
            result[i] = tuples[i].first;
            break;
        case 1:
            result[i] = tuples[i].second;
            break;
        case 2:
            result[i] = tuples[i].third;
            break;
        default:
            free(result);
            return NULL;
        }
    }

    return result;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 20, 300},
        {4, 50, 600},
        {7, 80, 900}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t n = 1U;
    int *extracted;
    size_t i;

    extracted = extract_nth(tuples, count, n);
    if (extracted == NULL) {
        fprintf(stderr, "Failed to extract element %zu\n", n);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%d%s", extracted[i], (i + 1 < count) ? " " : "\n");
    }

    free(extracted);
    return EXIT_SUCCESS;
}