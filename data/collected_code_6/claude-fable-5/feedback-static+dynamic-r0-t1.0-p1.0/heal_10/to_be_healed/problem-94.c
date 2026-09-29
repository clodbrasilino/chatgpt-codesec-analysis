#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    int value;
} Record;

int index_minimum(const Record *records, size_t count, char *result, size_t result_size)
{
    size_t i;
    size_t min_index;
    size_t name_len;

    if (records == NULL || result == NULL || count == 0 || result_size == 0) {
        return -1;
    }

    min_index = 0;
    for (i = 1; i < count; i++) {
        if (records[i].value < records[min_index].value) {
            min_index = i;
        }
    }

    name_len = strnlen(records[min_index].name, MAX_NAME_LEN);
    if (name_len >= MAX_NAME_LEN || name_len >= result_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, records[min_index].name, name_len);
    result[name_len] = '\0';

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
    char result[MAX_NAME_LEN];

    if (index_minimum(records, count, result, sizeof(result)) != 0) {
        fprintf(stderr, "Error: could not extract minimum record\n");
        return EXIT_FAILURE;
    }

    printf("Record with minimum value: %s\n", result);

    return EXIT_SUCCESS;
}