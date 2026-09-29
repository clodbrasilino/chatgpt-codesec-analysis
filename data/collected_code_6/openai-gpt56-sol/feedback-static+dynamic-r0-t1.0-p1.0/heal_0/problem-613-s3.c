#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int attribute;
} Record;

bool find_max_attribute(const Record *records, size_t count, int *maximum)
{
    if (records == NULL || maximum == NULL || count == 0U) {
        return false;
    }

    int current_maximum = records[0].attribute;

    for (size_t i = 1U; i < count; ++i) {
        if (records[i].attribute > current_maximum) {
            current_maximum = records[i].attribute;
        }
    }

    *maximum = current_maximum;
    return true;
}

int main(void)
{
    Record records[] = {
        {42},
        {-7},
        {105},
        {18},
        {64}
    };
    const size_t count = sizeof(records) / sizeof(records[0]);
    int maximum = 0;

    if (!find_max_attribute(records, count, &maximum)) {
        fputs("Failed to find the maximum attribute.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}