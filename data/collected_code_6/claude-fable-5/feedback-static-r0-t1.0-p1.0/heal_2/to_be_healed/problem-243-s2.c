#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 32

typedef struct {
    int key;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_NAME_LEN];
} Tuple;

static int tuple_init(Tuple *tuple, int key, const char *name)
{
    size_t name_len;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    name_len = strlen(name);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }

    tuple->key = key;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    (void)memcpy(tuple->value, name, name_len);
    tuple->value[name_len] = '\0';
    return 0;
}

static int sort_on_occurrence(const Tuple *input, size_t count, Tuple *output)
{
    size_t i;
    size_t j;
    size_t out_index;
    int *seen_keys;
    size_t seen_count;

    if (input == NULL || output == NULL || count == 0U) {
        return -1;
    }

    seen_keys = (int *)malloc(count * sizeof(int));
    if (seen_keys == NULL) {
        return -1;
    }

    seen_count = 0U;
    out_index = 0U;

    for (i = 0U; i < count; i++) {
        int already_seen = 0;
        for (j = 0U; j < seen_count; j++) {
            if (seen_keys[j] == input[i].key) {
                already_seen = 1;
                break;
            }
        }
        if (already_seen == 0) {
            seen_keys[seen_count] = input[i].key;
            seen_count++;
            for (j = 0U; j < count; j++) {
                if (input[j].key == input[i].key) {
                    output[out_index] = input[j];
                    out_index++;
                }
            }
        }
    }

    free(seen_keys);
    return 0;
}

int main(void)
{
    Tuple data[6];
    size_t count = sizeof(data) / sizeof(data[0]);
    Tuple *sorted;
    size_t i;
    int result;

    if (tuple_init(&data[0], 1, "Jake") != 0 ||
        tuple_init(&data[1], 2, "Bob") != 0 ||
        tuple_init(&data[2], 1, "Cara") != 0 ||
        tuple_init(&data[3], 3, "Ann") != 0 ||
        tuple_init(&data[4], 2, "Dan") != 0 ||
        tuple_init(&data[5], 1, "Eli") != 0) {
        (void)fprintf(stderr, "Tuple initialization failed\n");
        return EXIT_FAILURE;
    }

    sorted = (Tuple *)malloc(count * sizeof(Tuple));
    if (sorted == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = sort_on_occurrence(data, count, sorted);
    if (result != 0) {
        (void)fprintf(stderr, "Sorting failed\n");
        free(sorted);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%d, %s)\n", sorted[i].key, sorted[i].value) < 0) {
            free(sorted);
            return EXIT_FAILURE;
        }
    }

    free(sorted);
    return EXIT_SUCCESS;
}