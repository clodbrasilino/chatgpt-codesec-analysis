#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int value;
} Record;

int find_max_value(const Record *records, size_t count, int *maximum)
{
    if (records == NULL || maximum == NULL || count == 0U) {
        return 0;
    }

    *maximum = records[0].value;

    for (size_t i = 1U; i < count; ++i) {
        if (records[i].value > *maximum) {
            *maximum = records[i].value;
        }
    }

    return 1;
}

int main(void)
{
    const Record records[] = {
        {42},
        {17},
        {93},
        {58}
    };
    const size_t count = sizeof records / sizeof records[0];
    int maximum;

    if (!find_max_value(records, count, &maximum)) {
        fputs("Unable to find the maximum value.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}