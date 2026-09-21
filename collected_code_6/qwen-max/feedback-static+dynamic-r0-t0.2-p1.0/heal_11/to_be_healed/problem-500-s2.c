#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

char* concatenate_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] == NULL || !(*list[i])) continue;
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        total_length += strnlen(list[i], INT_MAX) + 1;
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    int current_len = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] == NULL || !(*list[i])) continue;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        size_t len = strnlen(list[i], INT_MAX);
        if (current_len + len + 1 > total_length) break;
        memmove(result + current_len, list[i], len);
        current_len += len;
        result[current_len++] = ' ';
    }
    if (current_len > 0) result[current_len - 1] = '\0';

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}