#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} RecordCount;

typedef struct {
    int frequency;
    int num_records;
} FreqGroup;

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
int check_similar_occurrences(int *data, int size, FreqGroup **groups, int *num_groups) {
    if (data == NULL || size <= 0 || groups == NULL || num_groups == NULL) {
        return -1;
    }

    RecordCount *counts = NULL;
    int unique_count = 0;
    int capacity = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (counts[j].value == data[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (unique_count >= capacity) {
                int new_capacity = capacity == 0 ? 16 : capacity * 2;
                RecordCount *new_counts = realloc(counts, (size_t)new_capacity * sizeof(RecordCount));
                if (new_counts == NULL) {
                    free(counts);
                    return -1;
                }
                counts = new_counts;
                capacity = new_capacity;
            }
            counts[unique_count].value = data[i];
            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count == 0) {
        free(counts);
        *groups = NULL;
        *num_groups = 0;
        return 0;
    }

    FreqGroup *result = NULL;
    int group_count = 0;
    int group_capacity = 0;

    for (int i = 0; i < unique_count; i++) {
        int found = 0;
        for (int j = 0; j < group_count; j++) {
            if (result[j].frequency == counts[i].count) {
                result[j].num_records++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (group_count >= group_capacity) {
                int new_capacity = group_capacity == 0 ? 16 : group_capacity * 2;
                FreqGroup *new_result = realloc(result, (size_t)new_capacity * sizeof(FreqGroup));
                if (new_result == NULL) {
                    free(counts);
                    free(result);
                    return -1;
                }
                result = new_result;
                group_capacity = new_capacity;
            }
            result[group_count].frequency = counts[i].count;
            result[group_count].num_records = 1;
            group_count++;
        }
    }

    free(counts);

    *groups = result;
    *num_groups = group_count;

    return 0;
}

int main(void) {
    int data[] = {1, 2, 3, 2, 3, 4, 1, 2, 5, 5, 6};
    int size = sizeof(data) / sizeof(data[0]);

    FreqGroup *groups = NULL;
    int num_groups = 0;

    int ret = check_similar_occurrences(data, size, &groups, &num_groups);
    if (ret != 0) {
        fprintf(stderr, "Error: failed to check similar occurrences\n");
        return 1;
    }

    printf("Records with similar occurrence counts:\n");
    for (int i = 0; i < num_groups; i++) {
        printf("  Frequency %d: %d record(s)\n", groups[i].frequency, groups[i].num_records);
    }

    printf("\nRecords occurring similar times:\n");
    int total_similar = 0;
    for (int i = 0; i < num_groups; i++) {
        if (groups[i].num_records > 1) {
            printf("  %d records occur %d time(s) each\n", groups[i].num_records, groups[i].frequency);
            total_similar += groups[i].num_records;
        }
    }
    if (total_similar == 0) {
        printf("  No records share the same occurrence count\n");
    }

    free(groups);

    return 0;
}