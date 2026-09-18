#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int* seconds;
    size_t count;
    size_t capacity;
} JoinedTuple;

JoinedTuple* join_tuples(const Tuple* tuples, size_t num_tuples, size_t* out_count) {
    if (!tuples || !out_count) {
        return NULL;
    }

    JoinedTuple* joined = NULL;
    size_t count = 0;
    size_t capacity = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        int found = 0;
        for (size_t j = 0; j < count; ++j) {
            if (joined[j].first == tuples[i].first) {
                if (joined[j].count >= joined[j].capacity) {
                    size_t new_cap = joined[j].capacity == 0 ? 4 : joined[j].capacity * 2;
                    int* new_seconds = realloc(joined[j].seconds, new_cap * sizeof(int));
                    if (!new_seconds) {
                        for (size_t k = 0; k < count; ++k) {
                            free(joined[k].seconds);
                        }
                        free(joined);
                        return NULL;
                    }
                    joined[j].seconds = new_seconds;
                    joined[j].capacity = new_cap;
                }
                joined[j].seconds[joined[j].count++] = tuples[i].second;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (count >= capacity) {
                size_t new_cap = capacity == 0 ? 4 : capacity * 2;
                JoinedTuple* new_joined = realloc(joined, new_cap * sizeof(JoinedTuple));
                if (!new_joined) {
                    for (size_t k = 0; k < count; ++k) {
                        free(joined[k].seconds);
                    }
                    free(joined);
                    return NULL;
                }
                joined = new_joined;
                capacity = new_cap;
            }

            joined[count].first = tuples[i].first;
            joined[count].capacity = 4;
            joined[count].count = 1;
            joined[count].seconds = malloc(joined[count].capacity * sizeof(int));
            if (!joined[count].seconds) {
                for (size_t k = 0; k < count; ++k) {
                    free(joined[k].seconds);
                }
                free(joined);
                return NULL;
            }
            joined[count].seconds[0] = tuples[i].second;
            count++;
        }
    }

    *out_count = count;
    return joined;
}

void free_joined_tuples(JoinedTuple* joined, size_t count) {
    if (joined) {
        for (size_t i = 0; i < count; ++i) {
            free(joined[i].seconds);
        }
        free(joined);
    }
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 30},
        {3, 40},
        {2, 50},
        {1, 60}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_count = 0;

    JoinedTuple* joined = join_tuples(tuples, num_tuples, &out_count);
    if (!joined) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < out_count; ++i) {
        printf("First: %d, Seconds: [", joined[i].first);
        for (size_t j = 0; j < joined[i].count; ++j) {
            printf("%d%s", joined[i].seconds[j], j < joined[i].count - 1 ? ", " : "");
        }
        printf("]\n");
    }

    free_joined_tuples(joined, out_count);
    return 0;
}