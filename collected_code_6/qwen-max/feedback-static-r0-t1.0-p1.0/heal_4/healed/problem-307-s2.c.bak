#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_colon_separated_value(const char *input, int n) {
    const char *start = input;
    const char *end;
    for (int i = 0; i < n; ++i) {
        end = strchr(start, ':');
        if (end == NULL) return NULL;
        start = end + 1;
    }
    size_t length = (end ? end - start : strlen(start));
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