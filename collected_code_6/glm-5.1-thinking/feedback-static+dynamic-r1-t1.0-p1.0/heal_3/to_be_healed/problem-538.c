#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t len;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->len; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['l', 'a', 'n', 'g', 'u', 'a', 'g', 'e'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['b', 'i', 'g', 'd', 'a', 't', 'a'], got <no output>
  */

Tuple *string_list_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = 0;
    while (len < 65536 && str[len] != '\0') {
        len++;
    }
    if (len == 65536) {
        return NULL;
    }
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->len = len;
    if (len == 0) {
        tuple->items = NULL;
        return tuple;
    }
    tuple->items = malloc(len * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        tuple->items[i] = malloc(2 * sizeof(char));
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        tuple->items[i][0] = str[i];
        tuple->items[i][1] = '\0';
    }
    return tuple;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            Tuple *tuple = string_list_to_tuple(argv[i]);
            if (tuple != NULL) {
                printf("[");
                for (size_t j = 0; j < tuple->len; j++) {
                    printf("'%s'", tuple->items[j]);
                    if (j < tuple->len - 1) {
                        printf(", ");
                    }
                }
                printf("]\n");
                free_tuple(tuple);
            } else {
                printf("[]\n");
            }
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[65536];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            size_t read_len = 0;
            while (read_len < sizeof(buffer) && buffer[read_len] != '\0') {
                read_len++;
            }
            if (read_len > 0 && buffer[read_len - 1] == '\n') {
                buffer[read_len - 1] = '\0';
                read_len--;
            }
            if (read_len > 0 && buffer[read_len - 1] == '\r') {
                buffer[read_len - 1] = '\0';
                /* Possible weaknesses found:
                 *  Variable 'read_len' is assigned a value that is never used. [unreadVariable]
                 */
                read_len--;
            }
            Tuple *tuple = string_list_to_tuple(buffer);
            if (tuple != NULL) {
                printf("[");
                for (size_t j = 0; j < tuple->len; j++) {
                    printf("'%s'", tuple->items[j]);
                    if (j < tuple->len - 1) {
                        printf(", ");
                    }
                }
                printf("]\n");
                free_tuple(tuple);
            } else {
                printf("[]\n");
            }
        }
    }
    return EXIT_SUCCESS;
}