#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const char *key;
    long long value;
} DictionaryItem;

static int dictionary_sum(const DictionaryItem *items, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (result == NULL || (items == NULL && count != 0U)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if ((items[i].value > 0 && sum > LLONG_MAX - items[i].value) ||
            (items[i].value < 0 && sum < LLONG_MIN - items[i].value)) {
            return -1;
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
    long long sum;

    if (dictionary_sum(dictionary,
                       sizeof(dictionary) / sizeof(dictionary[0]),
                       &sum) != 0) {
        (void)fprintf(stderr, "Failed to calculate the sum.\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}