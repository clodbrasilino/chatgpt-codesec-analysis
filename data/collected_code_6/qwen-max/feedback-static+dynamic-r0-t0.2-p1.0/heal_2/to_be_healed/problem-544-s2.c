#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;
    
    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]);
    }
    
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;
    
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strncat(result, list[i], total_length - strlen(result) + 1);
    }
    
    return result;
}

int main() {
    const char *tuple_list[] = {"(1,2)", "(3,4)", "(5,6)"};
    int size = 3;
    
    char *flattened = flatten_tuple_list(tuple_list, size);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten the tuple list.\n");
    }
    
    return 0;
}