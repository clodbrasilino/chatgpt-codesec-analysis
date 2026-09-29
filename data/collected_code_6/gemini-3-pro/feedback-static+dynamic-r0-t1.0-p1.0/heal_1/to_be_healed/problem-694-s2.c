#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[50];
    int value;
} DictionaryEntry;

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
bool isValueInArray(int *array, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}

int* extractUniqueValues(DictionaryEntry *dict, int dictSize, int *outSize) {
    if (dict == NULL || dictSize <= 0 || outSize == NULL) {
        if (outSize != NULL) *outSize = 0;
        return NULL;
    }

    int *uniqueValues = (int *)malloc(dictSize * sizeof(int));
    if (uniqueValues == NULL) {
        *outSize = 0;
        return NULL;
    }

    int uniqueCount = 0;

    for (int i = 0; i < dictSize; i++) {
        if (!isValueInArray(uniqueValues, uniqueCount, dict[i].value)) {
            uniqueValues[uniqueCount] = dict[i].value;
            uniqueCount++;
        }
    }

    int *resizedValues = (int *)realloc(uniqueValues, uniqueCount * sizeof(int));
    if (resizedValues != NULL) {
        uniqueValues = resizedValues;
    }

    *outSize = uniqueCount;
    return uniqueValues;
}

int main() {
    DictionaryEntry dict[] = {
        {"A", 10},
        {"B", 20},
        {"C", 10},
        {"D", 30},
        {"E", 20},
        {"F", 40}
    };
    int dictSize = sizeof(dict) / sizeof(dict[0]);
    int uniqueSize = 0;

    int *uniqueValues = extractUniqueValues(dict, dictSize, &uniqueSize);

    if (uniqueValues != NULL) {
        printf("Unique values: ");
        for (int i = 0; i < uniqueSize; i++) {
            printf("%d ", uniqueValues[i]);
        }
        printf("\n");
        free(uniqueValues);
    } else {
        printf("Memory allocation failed or empty dictionary.\n");
    }

    return 0;
}