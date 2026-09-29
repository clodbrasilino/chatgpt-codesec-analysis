#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;

    size_t len = strnlen(input, SIZE_MAX);
    if (len == 0 || len == SIZE_MAX) return NULL;

    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;

    tuple->len = len;
    tuple->str = malloc(tuple->len + 1);
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(tuple->str, input, tuple->len);
    tuple->str[tuple->len] = '\0';
    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *input = "Hello, World!";
    StringTuple *tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("Tuple: %s, Length: %zu\n", tuple->str, tuple->len);
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to create tuple.\n");
    }

    return 0;
}