#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    const char* name;
} Tuple;

char* flatten_tuples(Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    size_t current_size = 256;
    size_t used_size = 0;
    
    char* result = (char*)malloc(current_size);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        int expected_len = snprintf(NULL, 0, "%s(%d, \"%s\")", (i > 0) ? ", " : "", tuples[i].id, tuples[i].name);
        if (expected_len < 0) {
            free(result);
            return NULL;
        }

        while (used_size + expected_len + 1 >= current_size) {
            current_size *= 2;
            char* temp = (char*)realloc(result, current_size);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            result = temp;
        }

        int written = snprintf(result + used_size, current_size - used_size, "%s(%d, \"%s\")", 
                               (i > 0) ? ", " : "", tuples[i].id, tuples[i].name);
        if (written < 0 || (size_t)written >= current_size - used_size) {
            free(result);
            return NULL;
        }
        
        used_size += written;
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
    
    char* flattened = flatten_tuples(tuples, count);
    
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten tuples.\n");
        return 1;
    }
    
    return 0;
}