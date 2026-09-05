#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int *seconds;
    int count;
    int capacity;
} JoinedTuple;

JoinedTuple* join_tuples(Tuple* tuples, int num_tuples, int* result_size) {
    if (num_tuples == 0) {
        *result_size = 0;
        return NULL;
    }

    JoinedTuple* results = malloc(num_tuples * sizeof(JoinedTuple));
    if (!results) {
        *result_size = 0;
        return NULL;
    }

    int current_size = 0;

    for (int i = 0; i < num_tuples; i++) {
        if (current_size > 0 && results[current_size - 1].first == tuples[i].first) {
            JoinedTuple* current = &results[current_size - 1];
            if (current->count >= current->capacity) {
                current->capacity *= 2;
                int* temp = realloc(current->seconds, current->capacity * sizeof(int));
                if (!temp) {
                    for (int j = 0; j < current_size; j++) {
                        free(results[j].seconds);
                    }
                    free(results);
                    *result_size = 0;
                    return NULL;
                }
                current->seconds = temp;
            }
            current->seconds[current->count++] = tuples[i].second;
        } else {
            results[current_size].first = tuples[i].first;
            results[current_size].capacity = 4;
            results[current_size].seconds = malloc(results[current_size].capacity * sizeof(int));
            if (!results[current_size].seconds) {
                for (int j = 0; j < current_size; j++) {
                    free(results[j].seconds);
                }
                free(results);
                *result_size = 0;
                return NULL;
            }
            results[current_size].seconds[0] = tuples[i].second;
            results[current_size].count = 1;
            current_size++;
        }
    }

    *result_size = current_size;
    return results;
}

int main() {
    Tuple tuples[] = {{1, 2}, {1, 5}, {2, 3}, {3, 1}, {3, 4}, {3, 7}};
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int result_size = 0;

    JoinedTuple* joined = join_tuples(tuples, num_tuples, &result_size);

    if (joined) {
        for (int i = 0; i < result_size; i++) {
            printf("(%d, [", joined[i].first);
            for (int j = 0; j < joined[i].count; j++) {
                printf("%d", joined[i].seconds[j]);
                if (j < joined[i].count - 1) {
                    printf(", ");
                }
            }
            printf("])\n");
            free(joined[i].seconds);
        }
        free(joined);
    }

    return 0;
}