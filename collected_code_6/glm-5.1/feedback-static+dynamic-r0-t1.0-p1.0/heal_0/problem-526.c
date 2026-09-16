#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *capitalize_first_last(const char *str) {
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, str);

    if (len == 0) {
        return result;
    }

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
        
        if (isalpha((unsigned char)result[start])) {
            result[start] = (char)toupper((unsigned char)result[start]);
        }
        if (start != end && isalpha((unsigned char)result[end])) {
            result[end] = (char)toupper((unsigned char)result[end]);
        }
    }

    result[len] = '\0';
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