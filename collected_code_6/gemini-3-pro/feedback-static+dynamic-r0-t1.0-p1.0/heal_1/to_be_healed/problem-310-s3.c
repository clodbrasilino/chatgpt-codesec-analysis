#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  */

Tuple* string_to_tuple(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->elements = NULL;
    tuple->count = 0;

    char *str_copy = strdup(input);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
    }

    char *start = strchr(str_copy, '(');
    char *end = strrchr(str_copy, ')');
    
    if (start != NULL && end != NULL && start < end) {
        *end = '\0';
        char *token = strtok(start + 1, ",");
        
        while (token != NULL) {
            while (isspace((unsigned char)*token)) token++;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            char *end_token = token + strlen(token) - 1;
            while (end_token > token && isspace((unsigned char)*end_token)) {
                *end_token = '\0';
                end_token--;
            }
            
            char **new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char*));
            if (new_elements == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->elements[i]);
                }
                free(tuple->elements);
                free(tuple);
                free(str_copy);
                return NULL;
            }
            tuple->elements = new_elements;
            
            tuple->elements[tuple->count] = strdup(token);
            if (tuple->elements[tuple->count] == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->elements[i]);
                }
                free(tuple->elements);
                free(tuple);
                free(str_copy);
                return NULL;
            }
            
            tuple->count++;
            token = strtok(NULL, ",");
        }
    }

    free(str_copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *input_str = "(apple, banana, orange, grape)";
    
    Tuple *my_tuple = string_to_tuple(input_str);
    
    if (my_tuple != NULL) {
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("Element %zu: %s\n", i, my_tuple->elements[i]);
        }
        free_tuple(my_tuple);
    } else {
        printf("Failed to parse tuple.\n");
    }

    return 0;
}