#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'alloc_size=len/2+2', assigned value is greater than 1
     */
    size_t alloc_size = len / 2 + 2;
    /* Possible weaknesses found:
     *  Condition 'alloc_size==0' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size==0' is always false
     */
    if (alloc_size == 0) {
        return NULL;
    }

    char *result = malloc(alloc_size);
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = remove_odd_index_chars(input, input_len);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=remove_odd_index_chars(NULL,0)', assigned value is 0
     *  Calling function 'remove_odd_index_chars' returns 0
     */
    char *null_test = remove_odd_index_chars(NULL, 0);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_test==NULL' is always true
     */
    if (null_test == NULL) {
        printf("NULL input handled correctly.\n");
    } else {
        free(null_test);
    }

    return 0;
}