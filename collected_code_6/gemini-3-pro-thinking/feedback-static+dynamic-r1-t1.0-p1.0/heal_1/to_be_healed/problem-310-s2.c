#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple* create_tuple_from_string(const char *input, const char *delim);
void free_tuple(Tuple *tuple);

Tuple* create_tuple_from_string(const char *input, const char *delim) {
    if (!input || !delim) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *input_copy = malloc(strlen(input) + 1);
    if (!input_copy) {
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(input_copy, input);

    size_t count = 0;
    char *token = strtok(input_copy, delim);
    while (token) {
        count++;
        token = strtok(NULL, delim);
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(input_copy, input);

    if (count > 0) {
        tuple->items = malloc(count * sizeof(char*));
        if (!tuple->items) {
            free(input_copy);
            free(tuple);
            return NULL;
        }
    } else {
        tuple->items = NULL;
    }

    tuple->count = count;
    /* Possible weaknesses found:
     *  The scope of the variable 'idx' can be reduced. [variableScope]
     */
    size_t idx = 0;
    
    if (count > 0) {
        token = strtok(input_copy, delim);
        while (token) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            tuple->items[idx] = malloc(strlen(token) + 1);
            if (!tuple->items[idx]) {
                for (size_t i = 0; i < idx; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(input_copy);
                free(tuple);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(tuple->items[idx], token);
            idx++;
            token = strtok(NULL, delim);
        }
    }

    free(input_copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->items) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

int main(void) {
    const char *my_string = "apple,banana,orange,grape";
    const char *delimiter = ",";
    
    Tuple *my_tuple = create_tuple_from_string(my_string, delimiter);
    
    if (my_tuple) {
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("Tuple[%zu]: %s\n", i, my_tuple->items[i]);
        }
        free_tuple(my_tuple);
    }
    
    return 0;
}