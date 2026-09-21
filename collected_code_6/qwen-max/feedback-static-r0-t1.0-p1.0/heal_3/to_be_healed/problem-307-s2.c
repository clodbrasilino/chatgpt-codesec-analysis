#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_colon_separated_value(const char *input, int n) {
    const char *start = input;
    for (int i = 0; i < n; ++i) {
        const char *end = strchr(start, ':');
        if (end == NULL) return NULL;
        start = end + 1;
    }
    const char *end = strchr(start, ':');
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = (end == NULL) ? strlen(start) : end - start;
    char *result = (char *)malloc(length + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    (void)memcpy(result, start, length);
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