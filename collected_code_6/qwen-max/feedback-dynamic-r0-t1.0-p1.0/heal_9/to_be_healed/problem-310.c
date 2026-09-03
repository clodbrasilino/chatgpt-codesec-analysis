#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["python 3.0","
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

StringTuple *stringToTuple(const char *input) {
    if (input == NULL) return NULL;
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;
    tuple->len = strlen(input);
    tuple->str = (char *)malloc((tuple->len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    strcpy(tuple->str, input);
    return tuple;
}

void freeTuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *test_cases[] = {"python3.0", "15.10", "item1"};
    for (size_t i = 0; i < 3; ++i) {
        StringTuple *tuple = stringToTuple(test_cases[i]);
        if (tuple != NULL) {
            for (size_t j = 0; j < tuple->len; ++j) {
                printf("'%c'", tuple->str[j]);
            }
            printf("'\n'");
            freeTuple(tuple);
        } else {
            fprintf(stderr, "Failed to create tuple for: %s\n", test_cases[i]);
        }
    }
    return 0;
}