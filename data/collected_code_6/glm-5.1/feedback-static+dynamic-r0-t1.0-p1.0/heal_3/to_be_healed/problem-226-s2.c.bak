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
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
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
        output = NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'test_result=remove_odd_index_chars(NULL)', assigned value is 0
     *  Calling function 'remove_odd_index_chars' returns 0
     */
    char *test_result = remove_odd_index_chars(NULL);

    /* Possible weaknesses found:
     *  Condition 'test_result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test_result==NULL' is always true
     */
    if (test_result == NULL) {
        printf("NULL input handled correctly.\n");
    } else {
        free(test_result);
    }

    return 0;
}