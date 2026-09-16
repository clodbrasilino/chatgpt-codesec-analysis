#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Record;

static int count_before_record(const Record *tuple, size_t tuple_length,
                               Record target, size_t *count)
{
    if (tuple == NULL || count == NULL) {
        return 0;
    }

    for (size_t i = 0; i < tuple_length; ++i) {
        if (tuple[i].first == target.first &&
            tuple[i].second == target.second) {
            *count = i;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    Record tuple[] = {
        {10, 20},
        {30, 40},
        {50, 60},
        {70, 80}
    };
    const size_t tuple_length = sizeof(tuple) / sizeof(tuple[0]);
    const Record target = {50, 60};
    size_t count = 0;

    if (!count_before_record(tuple, tuple_length, target, &count)) {
        if (fprintf(stderr, "Record not found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}