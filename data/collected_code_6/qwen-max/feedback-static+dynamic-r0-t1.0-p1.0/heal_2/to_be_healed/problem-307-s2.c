#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_colon_separated_value(const char *input, int n) {
    const char *start = input;
    /* Possible weaknesses found:
     *  Assignment 'end=NULL', assigned value is 0
     */
    const char *end = NULL;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < n; ++i) {
        start = (i == 0) ? input : end + 1;
        end = strchr(start, ':');
        if (end == NULL) return NULL;
    }
    /* Possible weaknesses found:
     *  Null pointer subtraction
     *  Overflow in pointer arithmetic, NULL pointer is subtracted. [nullPointerArithmetic]
     */
    size_t len = end - start;
    char *result = malloc(len + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, start, len);
    result[len] = '\0';
    return result;
}

int main() {
    const char *tuple = "field1:field2:field3:field4";
    int n = 2;
    char *value = get_nth_colon_separated_value(tuple, n);
    if (value != NULL) {
        printf("%s\n", value);
        free(value);
    } else {
        printf("Value not found\n");
    }
    return 0;
}