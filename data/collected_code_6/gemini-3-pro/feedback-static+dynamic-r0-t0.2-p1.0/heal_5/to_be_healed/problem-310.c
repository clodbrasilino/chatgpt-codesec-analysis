#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    tuple->count = len;
    
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        tuple->elements[i] = malloc(2);
        if (tuple->elements[i]) {
            tuple->elements[i][0] = str[i];
            tuple->elements[i][1] = '\0';
        }
    }

    return tuple;
}

void print_tuple(Tuple *tuple) {
    if (!tuple) return;
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[2048];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        Tuple *t = string_to_tuple(buffer);
        if (t) {
            print_tuple(t);
            free_tuple(t);
        }
    }
    return 0;
}