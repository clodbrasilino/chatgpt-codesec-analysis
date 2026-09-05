#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *capitalize_first_last(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, str, len + 1);

    size_t i = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)result[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t start = i;
        while (i < len && !isspace((unsigned char)result[i])) {
            i++;
        }
        size_t end = i - 1;

        result[start] = (char)toupper((unsigned char)result[start]);
        result[end] = (char)toupper((unsigned char)result[end]);
    }

    return result;
}

int main(void) {
    const char *input = "hello world from c programming";
    char *output = capitalize_first_last(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%s\n", output);
    free(output);
    return 0;
}