#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[64];
    int value;
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[64];
    int aggregate;
} Aggregate;

char* calculate_max_aggregate(Tuple* tuples, int count) {
    if (tuples == NULL || count <= 0) {
        return NULL;
    }

    Aggregate* aggregates = (Aggregate*)malloc(count * sizeof(Aggregate));
    if (aggregates == NULL) {
        return NULL;
    }

    int agg_count = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < agg_count; j++) {
            if (strcmp(aggregates[j].key, tuples[i].key) == 0) {
                aggregates[j].aggregate += tuples[i].value;
                found = 1;
                break;
            }
        }
        if (!found) {
            snprintf(aggregates[agg_count].key, sizeof(aggregates[agg_count].key), "%s", tuples[i].key);
            aggregates[agg_count].aggregate = tuples[i].value;
            agg_count++;
        }
    }

    int max_index = 0;
    for (int i = 1; i < agg_count; i++) {
        if (aggregates[i].aggregate > aggregates[max_index].aggregate) {
            max_index = i;
        }
    }

    char* result = (char*)malloc(64 * sizeof(char));
    if (result != NULL) {
        snprintf(result, 64, "%s", aggregates[max_index].key);
    }

    free(aggregates);
    return result;
}

int main() {
    Tuple data[] = {
        {"A", 10},
        {"B", 20},
        {"A", 15},
        {"C", 5},
        {"B", 10},
        {"C", 30}
    };
    int count = sizeof(data) / sizeof(data[0]);

    char* max_key = calculate_max_aggregate(data, count);
    if (max_key != NULL) {
        printf("%s\n", max_key);
        free(max_key);
    } else {
        printf("Error calculating aggregate\n");
    }

    return 0;
}