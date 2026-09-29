#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_LEN];
    int value;
} Record;

int index_minimum(const Record *records, size_t count, char *out, size_t out_size)
{
    size_t i;
    size_t min_idx = 0;
    size_t name_len;

    if (records == NULL || out == NULL || count == 0U || out_size == 0U) {
        return -1;
    }

    for (i = 1U; i < count; i++) {
        if (records[i].value < records[min_idx].value) {
            min_idx = i;
        }
    }

    name_len = strnlen(records[min_idx].name, NAME_LEN);

    if (name_len >= NAME_LEN || name_len >= out_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(out, records[min_idx].name, name_len);
    out[name_len] = '\0';

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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