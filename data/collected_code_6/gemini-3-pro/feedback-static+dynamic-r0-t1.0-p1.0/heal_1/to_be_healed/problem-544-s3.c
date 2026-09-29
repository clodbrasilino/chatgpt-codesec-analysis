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

char* flatten_tuples(Tuple* tuples, size_t count) {
    if (!tuples || count == 0) {
        return NULL;
    }

    size_t initial_size = 256;
    size_t current_size = initial_size;
    size_t length = 0;
    
    char* result = (char*)malloc(current_size);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[100];
        int written = snprintf(buffer, sizeof(buffer), "(%d, %s)", tuples[i].id, tuples[i].name);
        
        if (written < 0) {
            free(result);
            return NULL;
        }

        if (length + written + 3 > current_size) {
            current_size *= 2;
            char* temp = (char*)realloc(result, current_size);
            if (!temp) {
                free(result);
                return NULL;
            }
            result = temp;
        }

        if (i > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncat(result, ", ", current_size - length - 1);
            length += 2;
        }
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, buffer, current_size - length - 1);
        length += (size_t)written;
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