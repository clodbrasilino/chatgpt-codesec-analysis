#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX_LEN 49

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_MAX_LEN + 1];
    double value;
} Tuple;

static int validate_tuple_name(const char *name) {
    if (name == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len <= NAME_MAX_LEN && name[len] != '\0') {
        len++;
    }
    
    return (len <= NAME_MAX_LEN && name[len] == '\0');
}

static size_t safe_add_size(size_t a, size_t b, size_t *result) {
    if (b > SIZE_MAX - a) {
        return 0;
    }
    *result = a + b;
    return 1;
}

char* flatten_tuple_list(const Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        char* empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    
    size_t total_size = 1;
    for (size_t i = 0; i < count; i++) {
        if (!validate_tuple_name(tuples[i].name)) {
            return NULL;
        }
        
        int needed = snprintf(NULL, 0, "(%d,%s,%.2f)", 
                              tuples[i].id, tuples[i].name, tuples[i].value);
        if (needed < 0) {
            return NULL;
        }
        
        size_t tuple_size = (size_t)needed + 1;
        if (!safe_add_size(total_size, tuple_size, &total_size)) {
            return NULL;
        }
    }
    
    char* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    size_t offset = 0;
    
    for (size_t i = 0; i < count; i++) {
        size_t remaining = total_size - offset;
        int written = snprintf(result + offset, remaining,
                               "(%d,%s,%.2f)", 
                               tuples[i].id, tuples[i].name, tuples[i].value);
        
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

static int init_tuple(Tuple *t, int id, const char *name, double value) {
    if (t == NULL || name == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t name_len = strlen(name);
    if (name_len > NAME_MAX_LEN) {
        return 0;
    }
    
    t->id = id;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(t->name, name, NAME_MAX_LEN);
    t->name[NAME_MAX_LEN] = '\0';
    t->value = value;
    
    return 1;
}

int main(void) {
    Tuple tuples[3];
    
    if (!init_tuple(&tuples[0], 1, "apple", 2.5) ||
        !init_tuple(&tuples[1], 2, "banana", 1.75) ||
        !init_tuple(&tuples[2], 3, "cherry", 3.0)) {
        fprintf(stderr, "Error: Failed to initialize tuples\n");
        return EXIT_FAILURE;
    }
    
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