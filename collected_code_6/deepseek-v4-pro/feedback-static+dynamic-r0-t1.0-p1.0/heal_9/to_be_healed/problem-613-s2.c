#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 31

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[32];
} Record;

typedef struct {
    Record record;
    int attribute;
} Tuple;

int find_max_attribute(const Tuple *tuples, size_t count, int *max_value) {
    if (tuples == NULL || count == 0 || max_value == NULL) {
        return -1;
    }

    *max_value = tuples[0].attribute;
    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].attribute > *max_value) {
            *max_value = tuples[i].attribute;
        }
    }
    return 0;
}

void print_record(const Record *record) {
    if (record == NULL) {
        return;
    }
    printf("ID: %d, Name: ", record->id);
    for (size_t i = 0; i < sizeof(record->name) && record->name[i] != '\0'; ++i) {
        putchar(record->name[i]);
    }
    putchar('\n');
}

Record create_record(int id, const char *name) {
    Record record;
    record.id = id;
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(name);
        if (len > MAX_NAME_LENGTH) {
            len = MAX_NAME_LENGTH;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(record.name, name, len);
        record.name[len] = '\0';
    } else {
        record.name[0] = '\0';
    }
    return record;
}

int main(void) {
    Tuple tuples[] = {
        {create_record(1, "Alice"), 25},
        {create_record(2, "Bob"), 42},
        {create_record(3, "Charlie"), 37},
        {create_record(4, "Diana"), 51}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int max_value = 0;

    if (find_max_attribute(tuples, count, &max_value) == 0) {
        printf("Maximum attribute value: %d\n", max_value);
        printf("\nRecords with maximum attribute:\n");
        for (size_t i = 0; i < count; ++i) {
            if (tuples[i].attribute == max_value) {
                print_record(&tuples[i].record);
            }
        }
    } else {
        fprintf(stderr, "Error: invalid input to find_max_attribute\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}