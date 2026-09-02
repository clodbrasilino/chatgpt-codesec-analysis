#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_colon_separated_value(const char *input, int n) {
    const char *start = input;
    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  'end' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'end'
         */
        if (i != 0) start = end + 1;
        const char *end = strchr(start, ':');
        if (end == NULL) return NULL;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'end'
     */
    size_t length = end - start;
    char *result = malloc(length + 1);
    if (result == NULL) return NULL;
    memcpy(result, start, length);
    result[length] = '\0';
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