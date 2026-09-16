#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int *seconds;
    size_t count;
} JoinedTuple;

JoinedTuple *join_tuples(const Tuple *tuples, size_t tuple_count, size_t *joined_count);
void free_joined_tuples(JoinedTuple *joined, size_t joined_count);

int main(void) {
    Tuple tuples[] = {
        {5, 6},
        {5, 7},
        {6, 8},
        {6, 10},
        {7, 13}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t joined_count = 0;
    JoinedTuple *joined = join_tuples(tuples, tuple_count, &joined_count);

    if (joined == NULL) {
        fprintf(stderr, "Failed to join tuples\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < joined_count; i++) {
        printf("%d", joined[i].first);
        for (size_t j = 0; j < joined[i].count; j++) {
            printf(" %d", joined[i].seconds[j]);
        }
        printf("\n");
    }

    free_joined_tuples(joined, joined_count);
    return EXIT_SUCCESS;
}

JoinedTuple *join_tuples(const Tuple *tuples, size_t tuple_count, size_t *joined_count) {
    if (joined_count == NULL) {
        return NULL;
    }

    *joined_count = 0;

    if (tuples == NULL || tuple_count == 0) {
        return NULL;
    }

    JoinedTuple *joined = malloc(tuple_count * sizeof(*joined));
    if (joined == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < tuple_count; i++) {
        int key = tuples[i].first;
        size_t pos = unique_count;

        for (size_t j = 0; j < unique_count; j++) {
            if (joined[j].first == key) {
                pos = j;
                break;
            }
        }

        if (pos == unique_count) {
            joined[unique_count].first = key;
            joined[unique_count].seconds = NULL;
            joined[unique_count].count = 0;
            unique_count++;
        }

        int *new_seconds = realloc(joined[pos].seconds,
                                   (joined[pos].count + 1) * sizeof(int));
        if (new_seconds == NULL) {
            for (size_t j = 0; j < unique_count; j++) {
                free(joined[j].seconds);
            }
            free(joined);
            return NULL;
        }

        joined[pos].seconds = new_seconds;
        joined[pos].seconds[joined[pos].count] = tuples[i].second;
        joined[pos].count++;
    }

    *joined_count = unique_count;
    return joined;
}

void free_joined_tuples(JoinedTuple *joined, size_t joined_count) {
    if (joined == NULL) {
        return;
    }

    for (size_t i = 0; i < joined_count; i++) {
        free(joined[i].seconds);
    }

    free(joined);
}