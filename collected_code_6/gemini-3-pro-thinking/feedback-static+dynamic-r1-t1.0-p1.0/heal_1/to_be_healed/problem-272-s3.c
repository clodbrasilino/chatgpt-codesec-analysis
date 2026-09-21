#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'TupleRecord::id' is never used. [unusedStructMember]
     */
    int id;
    char *value;
} TupleRecord;

static char *duplicate_string(const char *source) {
    size_t length;
    char *destination;

    if (!source) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source) + 1;
    destination = (char *)malloc(length);
    if (!destination) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(destination, source, length);
    return destination;
}

char **extract_rear_elements(const TupleRecord *records, size_t count) {
    char **rear_elements;
    size_t i;
    size_t j;

    if (!records || count == 0) {
        return NULL;
    }

    rear_elements = (char **)malloc(count * sizeof(char *));
    if (!rear_elements) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (records[i].value) {
            rear_elements[i] = duplicate_string(records[i].value);
            if (!rear_elements[i]) {
                for (j = 0; j < i; j++) {
                    free(rear_elements[j]);
                }
                free(rear_elements);
                return NULL;
            }
        } else {
            rear_elements[i] = NULL;
        }
    }

    return rear_elements;
}

int main(void) {
    TupleRecord records[] = {
        {101, "alpha"},
        {102, "bravo"},
        {103, "charlie"}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    char **extracted;
    size_t i;

    extracted = extract_rear_elements(records, count);
    if (!extracted) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (extracted[i]) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
    }
    free(extracted);

    return EXIT_SUCCESS;
}