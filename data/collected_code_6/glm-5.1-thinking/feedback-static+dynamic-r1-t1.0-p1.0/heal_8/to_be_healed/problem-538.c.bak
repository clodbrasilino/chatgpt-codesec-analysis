#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

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
  *  test case 1 failed: expected ['b', 'i', 'g', 'd', 'a', 't', 'a'], got <no output>
  *  test case 2 failed: expected ['l', 'a', 'n', 'g', 'u', 'a', 'g', 'e'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

Tuple *string_list_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->len = len;
    if (len == 0) {
        tuple->items = NULL;
        return tuple;
    }
    tuple->items = (char **)malloc(len * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        tuple->items[i] = (char *)malloc(2 * sizeof(char));
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

int main(int argc, char *argv[]) {
    char buffer[1024];
    const char *str = "python3.0";
    Tuple *tuple;
    if (argc > 1) {
        str = argv[1];
    } else {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;
        int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
        if (ready > 0) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n') {
                    buffer[len - 1] = '\0';
                }
                if (buffer[0] != '\0') {
                    str = buffer;
                }
            }
        }
    }
    tuple = string_list_to_tuple(str);
    if (tuple == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    printf("[");
    for (size_t i = 0; i < tuple->len; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("'%s'", tuple->items[i]);
    }
    printf("]\n");
    fflush(stdout);
    free_tuple(tuple);
    return EXIT_SUCCESS;
}