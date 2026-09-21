#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    const char *name;
} Tuple;

char* flatten_tuples(const Tuple* tuples, size_t count) {
    if (!tuples || count == 0) {
        return NULL;
    }

    size_t current_size = 256;
    size_t length = 0;
    
    char* result = (char*)malloc(current_size);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        int needed;
        if (i > 0) {
            needed = snprintf(NULL, 0, ", (%d, %s)", tuples[i].id, tuples[i].name);
        } else {
            needed = snprintf(NULL, 0, "(%d, %s)", tuples[i].id, tuples[i].name);
        }
        
        if (needed < 0) {
            free(result);
            return NULL;
        }

        while (length + (size_t)needed + 1 > current_size) {
            current_size *= 2;
            char* temp = (char*)realloc(result, current_size);
            if (!temp) {
                free(result);
                return NULL;
            }
            result = temp;
        }

        if (i > 0) {
            snprintf(result + length, current_size - length, ", (%d, %s)", tuples[i].id, tuples[i].name);
        } else {
            snprintf(result + length, current_size - length, "(%d, %s)", tuples[i].id, tuples[i].name);
        }
        
        length += (size_t)needed;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, "Apple"},
        {2, "Banana"},
        {3, "Cherry"}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    char* flattened = flatten_tuples(tuples, count);
    if (flattened) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}