#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    int64_t value;
} DictionaryItem;

static int sum_dictionary(const DictionaryItem *items, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (items == NULL && count != 0U)) {
        return EINVAL;
    }

    for (size_t i = 0; i < count; ++i) {
        const int64_t value = items[i].value;

        if ((value > 0 && sum > INT64_MAX - value) ||
            (value < 0 && sum < INT64_MIN - value)) {
            return ERANGE;
        }

        sum += value;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const DictionaryItem dictionary[] = {
        {10},
        {20},
        {30}
    };
    int64_t sum = 0;
    const size_t count = sizeof(dictionary) / sizeof(dictionary[0]);
    const int status = sum_dictionary(dictionary, count, &sum);

    if (status != 0) {
        fprintf(stderr, "Unable to calculate the sum: error %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Sum: %" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}