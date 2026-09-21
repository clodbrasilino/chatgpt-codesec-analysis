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

    if (records == NULL || out == NULL || count == 0U || out_size == 0U) {
        return -1;
    }

    for (i = 1U; i < count; i++) {
        if (records[i].value < records[min_idx].value) {
            min_idx = i;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(records[min_idx].name) >= out_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
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