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
     *  Overflow in pointer arithmetic, NULL pointer is subtracted. [nullPointerArithmetic]
     *  Null pointer subtraction
     */
    char *result = malloc(end - start + 1);
    if (result == NULL) return NULL;
    memcpy(result, start, end - start);
    result[end - start] = '\0';
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