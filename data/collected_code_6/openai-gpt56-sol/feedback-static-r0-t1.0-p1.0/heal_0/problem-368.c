#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int repeat_tuple(const Tuple *tuple, size_t count, Tuple **result)
{
    Tuple *items;

    if (tuple == NULL || result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*items)) {
        return EOVERFLOW;
    }

    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < count; ++i) {
        items[i] = *tuple;
    }

    *result = items;
    return 0;
}

int main(void)
{
    Tuple tuple;
    Tuple *repeated = NULL;
    size_t count;
    int status;

    if (printf("Enter two integers and a repetition count: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d %d %zu", &tuple.first, &tuple.second, &count) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = repeat_tuple(&tuple, count, &repeated);
    if (status != 0) {
        errno = status;
        perror("repeat_tuple");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)%c",
                   repeated[i].first,
                   repeated[i].second,
                   i + 1 == count ? '\n' : ' ') < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
    }

    if (count == 0 && putchar('\n') == EOF) {
        free(repeated);
        return EXIT_FAILURE;
    }

    free(repeated);
    return EXIT_SUCCESS;
}