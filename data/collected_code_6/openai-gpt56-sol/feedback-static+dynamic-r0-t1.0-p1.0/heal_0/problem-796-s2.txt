#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    const char *key;
    int64_t value;
} DictionaryItem;

static int sum_dictionary(const DictionaryItem *items, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (items == NULL && count != 0U)) {
        return EINVAL;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((items[i].value > 0 && sum > INT64_MAX - items[i].value) ||
            (items[i].value < 0 && sum < INT64_MIN - items[i].value)) {
            return ERANGE;
        }

        sum += items[i].value;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const DictionaryItem dictionary[] = {
        {"apple", 10},
        {"banana", 20},
        {"orange", 30}
    };
    int64_t sum = 0;
    const int status = sum_dictionary(
        dictionary,
        sizeof(dictionary) / sizeof(dictionary[0]),
        &sum
    );

    if (status != 0) {
        fprintf(stderr, "Unable to calculate the sum: error %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Sum: %" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}