#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tuple_to_string(const int *tuple, size_t len) {
    if (len == 0) return NULL;
    size_t string_length = len * 2 - 1; // spaces between numbers and null terminator
    char *result = (char *)malloc(string_length + 1);
    if (result == NULL) return NULL;

    size_t pos = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i != 0) {
            result[pos++] = ' ';
        }
        pos += snprintf(result + pos, string_length - pos + 1, "%d", tuple[i]);
    }
    result[pos] = '\0';
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);

    char *str = tuple_to_string(tuple, len);
    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}