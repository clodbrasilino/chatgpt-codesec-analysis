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

static int sort_on_occurrence(const Tuple *input, size_t count, Tuple *output)
{
    size_t i;
    size_t j;
    size_t out_index;
    int *seen_keys;
    size_t seen_count;
    /* Possible weaknesses found:
     *  The scope of the variable 'already_seen' can be reduced. [variableScope]
     */
    int already_seen;

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
        already_seen = 0;
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
    Tuple data[] = {
        {1, "Jake"},
        {2, "Bob"},
        {1, "Cara"},
        {3, "Ann"},
        {2, "Dan"},
        {1, "Eli"}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    Tuple *sorted;
    size_t i;
    int result;

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