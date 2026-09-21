#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    char key[64];
    int value;
} DictionaryEntry;

typedef struct {
    int *values;
    size_t count;
} UniqueResult;

UniqueResult extract_unique_values(const DictionaryEntry *dict, size_t dict_size) {
    UniqueResult result = {NULL, 0};

    if (dict == NULL || dict_size == 0) {
        return result;
    }

    int *temp_values = (int *)malloc(dict_size * sizeof(int));
    if (temp_values == NULL) {
        return result;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < dict_size; i++) {
        int is_unique = 1;
        for (size_t j = 0; j < unique_count; j++) {
            if (temp_values[j] == dict[i].value) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            if (unique_count < dict_size) {
                temp_values[unique_count++] = dict[i].value;
            }
        }
    }

    if (unique_count > 0) {
        result.values = (int *)malloc(unique_count * sizeof(int));
        if (result.values != NULL) {
            if (unique_count <= dict_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result.values, temp_values, unique_count * sizeof(int));
            }
            result.count = unique_count;
        }
    }

    free(temp_values);
    return result;
}

void free_unique_result(UniqueResult *result) {
    if (result != NULL) {
        free(result->values);
        result->values = NULL;
        result->count = 0;
    }
}

int main(void) {
    DictionaryEntry dict[] = {
        {"apple", 5},
        {"banana", 3},
        {"cherry", 5},
        {"date", 7},
        {"elderberry", 3},
        {"fig", 9}
    };
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);

    UniqueResult result = extract_unique_values(dict, dict_size);

    if (result.values != NULL) {
        for (size_t i = 0; i < result.count; i++) {
            printf("%d\n", result.values[i]);
        }
    }

    free_unique_result(&result);

    return 0;
}