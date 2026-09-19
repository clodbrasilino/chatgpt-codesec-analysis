#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int value;
} Record;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'RecordGroup::records' is never used. [unusedStructMember]
     */
    Record *records;
    /* Possible weaknesses found:
     *  struct member 'RecordGroup::count' is never used. [unusedStructMember]
     */
    int count;
} RecordGroup;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'OccurrenceArray::occurrences' is never used. [unusedStructMember]
     */
    int *occurrences;
    /* Possible weaknesses found:
     *  struct member 'OccurrenceArray::size' is never used. [unusedStructMember]
     */
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
            strcmp(records[i].name, target->name) == 0 &&
            records[i].value == target->value) {
            occurrences++;
        }
    }
    return occurrences;
}

static int is_duplicate(const Record *unique_records, int unique_count, const Record *target) {
    for (int i = 0; i < unique_count; i++) {
        if (unique_records[i].id == target->id &&
            strcmp(unique_records[i].name, target->name) == 0 &&
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

    Record *unique_records = (Record *)malloc((size_t)count * sizeof(Record));
    if (unique_records == NULL) {
        return -1;
    }

    int unique_count = 0;
    for (int i = 0; i < count; i++) {
        if (!is_duplicate(unique_records, unique_count, &records[i])) {
            unique_records[unique_count] = records[i];
            unique_count++;
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
    Record records[] = {
        {1, "alpha", 100},
        {2, "beta", 200},
        {1, "alpha", 100},
        {3, "gamma", 300},
        {2, "beta", 200},
        {3, "gamma", 300}
    };
    int count = sizeof(records) / sizeof(records[0]);

    int result = check_similar_occurrences(records, count);
    if (result == 1) {
        printf("All records occur similar times\n");
    } else if (result == 0) {
        printf("Records do not occur similar times\n");
    } else {
        printf("Error processing records\n");
    }

    Record records2[] = {
        {1, "alpha", 100},
        {2, "beta", 200},
        {1, "alpha", 100},
        {3, "gamma", 300}
    };
    count = sizeof(records2) / sizeof(records2[0]);

    result = check_similar_occurrences(records2, count);
    if (result == 1) {
        printf("All records occur similar times\n");
    } else if (result == 0) {
        printf("Records do not occur similar times\n");
    } else {
        printf("Error processing records\n");
    }

    return 0;
}