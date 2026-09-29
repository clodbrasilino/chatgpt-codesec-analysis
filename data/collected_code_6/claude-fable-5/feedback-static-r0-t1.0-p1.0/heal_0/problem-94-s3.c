#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64

typedef struct {
    char name[NAME_LEN];
    int value;
} Record;

int index_minimum(const Record *records, size_t count, char *out, size_t out_size)
{
    size_t i;
    size_t min_idx = 0;

    if (records == NULL || out == NULL || count == 0U || out_size == 0U) {
        return -1;
    }

    for (i = 1U; i < count; i++) {
        if (records[i].value < records[min_idx].value) {
            min_idx = i;
        }
    }

    if (strlen(records[min_idx].name) >= out_size) {
        return -1;
    }

    strncpy(out, records[min_idx].name, out_size - 1U);
    out[out_size - 1U] = '\0';

    return 0;
}

int main(void)
{
    Record records[] = {
        {"Rash", 143},
        {"Manjeet", 200},
        {"Varsha", 100}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    char result[NAME_LEN];

    if (index_minimum(records, count, result, sizeof(result)) != 0) {
        (void)fprintf(stderr, "Error: could not extract minimum record\n");
        return EXIT_FAILURE;
    }

    if (printf("Record with minimum value: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}