#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    char *output = remove_odd_index_chars(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    const char *null_input = NULL;
    /* Possible weaknesses found:
     *  Assignment 'null_output=remove_odd_index_chars(null_input)', assigned value is 0
     *  Calling function 'remove_odd_index_chars' returns 0
     *  Variable 'null_output' can be declared as pointer to const [constVariablePointer]
     */
    char *null_output = remove_odd_index_chars(null_input);
    /* Possible weaknesses found:
     *  Condition 'null_output==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_output==NULL' is always true
     */
    if (null_output == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}