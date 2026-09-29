#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *str, char *result, size_t result_size) {
    if (result_size == 0) return NULL;
    int j = 0;
    for (int i = 0; str[i] && j < result_size - 1; i++) {
        if (isupper(str[i])) {
            if (i > 0 && str[i - 1] != '_') {
                if (j >= result_size - 2) break;
                result[j++] = '_';
            }
            if (j >= result_size - 1) break;
            result[j++] = tolower(str[i]);
        } else {
            if (j >= result_size - 1) break;
            result[j++] = str[i];
        }
    }
    result[j < result_size - 1 ? j : result_size - 1] = '\0';
    return result;
}

int main() {
    const char input[] = "ThisIsACamelCaseString";
    char result[256];
    camel_to_snake(input, result, sizeof(result));
    printf("%s\n", result);
    return 0;
}