#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    long long value;
} DictionaryEntry;

static int sum_dictionary(const DictionaryEntry *dictionary,
                          size_t count,
                          long long *sum)
{
    size_t i;
    long long total = 0;

    if (sum == NULL || (dictionary == NULL && count != 0)) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if ((dictionary[i].value > 0 && total > LLONG_MAX - dictionary[i].value) ||
            (dictionary[i].value < 0 && total < LLONG_MIN - dictionary[i].value)) {
            return 0;
        }
        total += dictionary[i].value;
    }

    *sum = total;
    return 1;
}

int main(void)
{
    const DictionaryEntry dictionary[] = {
        {"apple", 10},
        {"banana", 20},
        {"orange", 30}
    };
    long long sum;

    if (!sum_dictionary(dictionary,
                        sizeof(dictionary) / sizeof(dictionary[0]),
                        &sum)) {
        fputs("Unable to calculate sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}