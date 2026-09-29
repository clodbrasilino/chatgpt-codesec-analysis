#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <limits.h>

#define NAME_SIZE 50
#define MAX_TUPLES 1000
#define MAX_FLATTENED_SIZE (1024 * 1024)

typedef struct {
    int id;
    char name[NAME_SIZE];
    double value;
} Tuple;

static bool is_valid_name(const char *name) {
    if (name == NULL) {
        return false;
    }
    size_t len = strnlen(name, NAME_SIZE);
    return len < NAME_SIZE;
}

char* flatten_tuple_list(const Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        char* empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    
    if (count > MAX_TUPLES) {
        return NULL;
    }
    
    size_t total_size = 1;
    for (size_t i = 0; i < count; i++) {
        if (!is_valid_name(tuples[i].name)) {
            return NULL;
        }
        
        int needed = snprintf(NULL, 0, "(%d,%.*s,%.2f)", 
                              tuples[i].id, NAME_SIZE - 1, tuples[i].name, tuples[i].value);
        if (needed < 0) {
            return NULL;
        }
        
        if ((size_t)needed > MAX_FLATTENED_SIZE - total_size - 1) {
            return NULL;
        }
        total_size += (size_t)needed + 1;
    }
    
    char* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    
    for (size_t i = 0; i < count; i++) {
        size_t remaining = total_size - offset;
        int written = snprintf(result + offset, remaining, 
                               "(%d,%.*s,%.2f)", 
                               tuples[i].id, NAME_SIZE - 1, tuples[i].name, tuples[i].value);
        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            return NULL;
        }
        offset += (size_t)written;
        
        if (i < count - 1) {
            if (offset >= total_size - 1) {
                free(result);
                return NULL;
            }
            result[offset] = ',';
            offset++;
            result[offset] = '\0';
        }
    }
    
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, "apple", 2.5},
        {2, "banana", 1.75},
        {3, "cherry", 3.0}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    char* flattened = flatten_tuple_list(tuples, count);
    
    if (flattened == NULL) {
        fprintf(stderr, "Error: Failed to flatten tuple list\n");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", flattened);
    free(flattened);
    
    return EXIT_SUCCESS;
}