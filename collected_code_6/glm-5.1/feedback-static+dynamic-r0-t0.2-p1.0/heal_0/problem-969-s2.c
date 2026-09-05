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
    if (tuples == NULL || num_tuples <= 0 || result_size == NULL) {
        if (result_size != NULL) *result_size = 0;
        return NULL;
    }

    JoinedTuple* result = (JoinedTuple*)malloc(num_tuples * sizeof(JoinedTuple));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int current_size = 0;

    for (int i = 0; i < num_tuples; i++) {
        int found = -1;
        for (int j = 0; j < current_size; j++) {
            if (result[j].first == tuples[i].first) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            if (result[found].count >= result[found].capacity) {
                int new_capacity = result[found].capacity * 2;
                int* temp = (int*)realloc(result[found].seconds, new_capacity * sizeof(int));
                if (temp == NULL) {
                    for (int k = 0; k < current_size; k++) {
                        free(result[k].seconds);
                    }
                    free(result);
                    *result_size = 0;
                    return NULL;
                }
                result[found].seconds = temp;
                result[found].capacity = new_capacity;
            }
            result[found].seconds[result[found].count++] = tuples[i].second;
        } else {
            result[current_size].first = tuples[i].first;
            result[current_size].capacity = 4;
            result[current_size].seconds = (int*)malloc(result[current_size].capacity * sizeof(int));
            if (result[current_size].seconds == NULL) {
                for (int k = 0; k < current_size; k++) {
                    free(result[k].seconds);
                }
                free(result);
                *result_size = 0;
                return NULL;
            }
            result[current_size].count = 1;
            result[current_size].seconds[0] = tuples[i].second;
            current_size++;
        }
    }

    *result_size = current_size;
    return result;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 5}, {6, 7}, {3, 8}, {1, 9}};
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int result_size = 0;

    JoinedTuple* joined = join_tuples(tuples, num_tuples, &result_size);

    if (joined != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("{%d, [", joined[i].first);
            for (int j = 0; j < joined[i].count; j++) {
                printf("%d", joined[i].seconds[j]);
                if (j < joined[i].count - 1) {
                    printf(", ");
                }
            }
            printf("]}\n");
            free(joined[i].seconds);
        }
        free(joined);
    }

    return 0;
}