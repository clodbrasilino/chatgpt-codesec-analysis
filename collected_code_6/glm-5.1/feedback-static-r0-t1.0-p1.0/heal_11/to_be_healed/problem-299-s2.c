#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 64
#define KEY_MAX_LEN (KEY_SIZE - 1)

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    int value;
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    int aggregate;
} Aggregate;

char* calculate_max_aggregate(Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    Aggregate* aggregates = malloc(count * sizeof(Aggregate));
    if (aggregates == NULL) {
        return NULL;
    }

    size_t agg_count = 0;

    for (size_t i = 0; i < count; i++) {
        if (strnlen(tuples[i].key, KEY_SIZE) == KEY_SIZE) {
            continue;
        }
        
        int found = 0;
        for (size_t j = 0; j < agg_count; j++) {
            if (strncmp(aggregates[j].key, tuples[i].key, KEY_SIZE) == 0) {
                aggregates[j].aggregate += tuples[i].value;
                found = 1;
                break;
            }
        }
        if (!found) {
            snprintf(aggregates[agg_count].key, KEY_SIZE, "%s", tuples[i].key);
            aggregates[agg_count].aggregate = tuples[i].value;
            agg_count++;
        }
    }

    if (agg_count == 0) {
        free(aggregates);
        return NULL;
    }

    size_t max_index = 0;
    for (size_t i = 1; i < agg_count; i++) {
        if (aggregates[i].aggregate > aggregates[max_index].aggregate) {
            max_index = i;
        }
    }

    char* result = malloc(KEY_SIZE * sizeof(char));
    if (result != NULL) {
        snprintf(result, KEY_SIZE, "%s", aggregates[max_index].key);
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
    size_t count = sizeof(data) / sizeof(data[0]);

    char* max_key = calculate_max_aggregate(data, count);
    if (max_key != NULL) {
        printf("%s\n", max_key);
        free(max_key);
    } else {
        printf("Error calculating aggregate\n");
    }

    return 0;
}