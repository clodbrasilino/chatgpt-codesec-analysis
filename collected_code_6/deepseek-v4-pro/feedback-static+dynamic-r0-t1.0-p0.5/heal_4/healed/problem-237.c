#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
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

static int count_occurrences(const RecordGroup *group, const Record *target) {
    int occurrences = 0;
    for (int i = 0; i < group->count; i++) {
        if (group->records[i].id == target->id &&
            strcmp(group->records[i].name, target->name) == 0 &&
            group->records[i].value == target->value) {
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

static int check_similar_occurrences(const RecordGroup *group) {
    if (group == NULL || group->records == NULL || group->count <= 0) {
        return 0;
    }

    Record *unique_records = (Record *)malloc((size_t)group->count * sizeof(Record));
    if (unique_records == NULL) {
        return -1;
    }

    int unique_count = 0;
    for (int i = 0; i < group->count; i++) {
        if (!is_duplicate(unique_records, unique_count, &group->records[i])) {
            unique_records[unique_count] = group->records[i];
            unique_count++;
        }
    }

    int *occurrences = (int *)malloc((size_t)unique_count * sizeof(int));
    if (occurrences == NULL) {
        free(unique_records);
        return -1;
    }

    for (int i = 0; i < unique_count; i++) {
        occurrences[i] = count_occurrences(group, &unique_records[i]);
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

    RecordGroup group;
    group.records = records;
    group.count = sizeof(records) / sizeof(records[0]);

    int result = check_similar_occurrences(&group);
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

    group.records = records2;
    group.count = sizeof(records2) / sizeof(records2[0]);

    result = check_similar_occurrences(&group);
    if (result == 1) {
        printf("All records occur similar times\n");
    } else if (result == 0) {
        printf("Records do not occur similar times\n");
    } else {
        printf("Error processing records\n");
    }

    return 0;
}