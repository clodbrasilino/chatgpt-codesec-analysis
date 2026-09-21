#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    int value;
} Record;

typedef struct {
    Record *records;
    int count;
} RecordGroup;

typedef struct {
    int *occurrences;
    int size;
} OccurrenceArray;

static int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

static int count_occurrences(const Record *records, int count, const Record *target) {
    int occurrences = 0;
    for (int i = 0; i < count; i++) {
        if (records[i].id == target->id &&
            strncmp(records[i].name, target->name, sizeof(records[i].name) - 1) == 0 &&
            records[i].value == target->value) {
            occurrences++;
        }
    }
    return occurrences;
}

static int is_duplicate(const Record *unique_records, int unique_count, const Record *target) {
    for (int i = 0; i < unique_count; i++) {
        if (unique_records[i].id == target->id &&
            strncmp(unique_records[i].name, target->name, sizeof(unique_records[i].name) - 1) == 0 &&
            unique_records[i].value == target->value) {
            return 1;
        }
    }
    return 0;
}

static int check_similar_occurrences(const Record *records, int count) {
    if (records == NULL || count <= 0) {
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (records[i].name[sizeof(records[i].name) - 1] != '\0') {
            return -1;
        }
    }

    Record *unique_records = (Record *)malloc((size_t)count * sizeof(Record));
    if (unique_records == NULL) {
        return -1;
    }

    int unique_count = 0;
    for (int i = 0; i < count; i++) {
        if (!is_duplicate(unique_records, unique_count, &records[i])) {
            if (unique_count < count) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(&unique_records[unique_count], &records[i], sizeof(Record));
                unique_count++;
            }
        }
    }

    int *occurrences = (int *)malloc((size_t)unique_count * sizeof(int));
    if (occurrences == NULL) {
        free(unique_records);
        return -1;
    }

    for (int i = 0; i < unique_count; i++) {
        occurrences[i] = count_occurrences(records, count, &unique_records[i]);
    }

    qsort(occurrences, (size_t)unique_count, sizeof(int), compare_ints);

    int result = 1;
    for (int i = 1; i < unique_count; i++) {
        if (occurrences[i] != occurrences[0]) {
            result = 0;
            break;
        }
    }

    free(unique_records);
    free(occurrences);
    return result;
}

int main(void) {
    RecordGroup group1;
    group1.records = (Record[]) {
        {1, "alpha", 100},
        {2, "beta", 200},
        {1, "alpha", 100},
        {3, "gamma", 300},
        {2, "beta", 200},
        {3, "gamma", 300}
    };
    group1.count = 6;

    int result = check_similar_occurrences(group1.records, group1.count);
    if (result == 1) {
        printf("All records occur similar times\n");
    } else if (result == 0) {
        printf("Records do not occur similar times\n");
    } else {
        printf("Error processing records\n");
    }

    RecordGroup group2;
    group2.records = (Record[]) {
        {1, "alpha", 100},
        {2, "beta", 200},
        {1, "alpha", 100},
        {3, "gamma", 300}
    };
    group2.count = 4;

    OccurrenceArray occ_array;
    occ_array.occurrences = NULL;
    /* Possible weaknesses found:
     *  Variable 'occ_array.size' is assigned a value that is never used. [unreadVariable]
     */
    occ_array.size = 0;

    result = check_similar_occurrences(group2.records, group2.count);
    if (result == 1) {
        printf("All records occur similar times\n");
    } else if (result == 0) {
        printf("Records do not occur similar times\n");
    } else {
        printf("Error processing records\n");
    }

    occ_array.occurrences = (int *)malloc((size_t)group2.count * sizeof(int));
    if (occ_array.occurrences != NULL) {
        for (int i = 0; i < group2.count; i++) {
            occ_array.occurrences[i] = i;
        }
        occ_array.size = group2.count;
        printf("Occurrence array size: %d\n", occ_array.size);
        free(occ_array.occurrences);
        occ_array.occurrences = NULL;
        /* Possible weaknesses found:
         *  Variable 'occ_array.size' is assigned a value that is never used. [unreadVariable]
         */
        occ_array.size = 0;
    }

    return 0;
}