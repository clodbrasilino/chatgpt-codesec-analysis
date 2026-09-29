#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
} Tuple;

char* flatten_tuples(Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    size_t initial_size = 256;
    size_t current_size = initial_size;
    size_t used_size = 0;
    
    char* result = (char*)malloc(current_size);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        char buffer[100];
        int written = snprintf(buffer, sizeof(buffer), "(%d, %s)", tuples[i].id, tuples[i].name);
        
        if (written < 0) {
            free(result);
            return NULL;
        }

        if (used_size + written + 2 >= current_size) {
            current_size *= 2;
            char* temp = (char*)realloc(result, current_size);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            result = temp;
        }

        if (i > 0) {
            strncat(result, ", ", current_size - used_size - 1);
            used_size += 2;
        }
        
        strncat(result, buffer, current_size - used_size - 1);
        used_size += written;
    }

    return result;
}

int main() {
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