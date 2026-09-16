#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int value;
} Tuple;

typedef struct {
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
            strncpy(aggregates[agg_count].key, tuples[i].key, 63);
            aggregates[agg_count].key[63] = '\0';
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
        strncpy(result, aggregates[max_index].key, 63);
        result[63] = '\0';
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