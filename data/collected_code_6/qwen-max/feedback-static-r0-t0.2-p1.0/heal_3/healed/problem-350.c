#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* minimize_string_length(const char *str, char ch) {
    size_t len = 0;
    while (str[len] != '\0') len++;

    int count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    char *result = (char *)malloc((len - count + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ch) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main() {
    const char str[] = "example string with some characters";
    char ch = 'e';
    char *minimized_str = minimize_string_length(str, ch);

    if (minimized_str != NULL) {
        printf("Minimized string: %s\n", minimized_str);
        free(minimized_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}