#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} Tuple;

char* flatten_tuples_to_string(const Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        total_length += (size_t)snprintf(NULL, 0, "(%d, %s)", tuples[i].id, tuples[i].name) + 1;
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;

    for (size_t i = 0; i < count; i++) {
        int written = snprintf(result + current_length, total_length - current_length + 1,
                               "(%d, %s)%s", tuples[i].id, tuples[i].name, (i < count - 1) ? ", " : "");
        if (written < 0) {
            free(result);
            return NULL;
        }
        current_length += (size_t)written;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    char* flattened_string = flatten_tuples_to_string(tuples, count);

    if (flattened_string != NULL) {
        printf("%s\n", flattened_string);
        free(flattened_string);
    } else {
        printf("Failed to flatten tuples.\n");
    }

    return 0;
}