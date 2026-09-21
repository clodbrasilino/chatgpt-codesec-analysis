#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

StringTuple *stringToTuple(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->len = len;
    tuple->str = (char *)malloc((len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->str, input, len);
    tuple->str[len] = '\0';
    return tuple;
}

void freeTuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *inputs[] = {"python3.0", "item1", "15.10", "Hello, World!"};
    for (size_t i = 0; i < 4; ++i) {
        StringTuple *tuple = stringToTuple(inputs[i]);
        if (tuple != NULL) {
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c' ", tuple->str[j]);
            }
            printf("\n");
            freeTuple(tuple);
        } else {
            fprintf(stderr, "Failed to create tuple\n");
        }
    }
    return 0;
}