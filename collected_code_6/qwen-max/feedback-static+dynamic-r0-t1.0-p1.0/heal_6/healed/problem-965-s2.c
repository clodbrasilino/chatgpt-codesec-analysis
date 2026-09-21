#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }
    size_t len = strlen(str);
    char *result = (char *)malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper(str[i]) && i > 0 && str[i - 1] != '_') {
            result[j++] = '_';
        }
        result[j++] = tolower(str[i]);
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *input[] = {"PythonProgram", "Python_Language", "ProgrammingLanguage"};
    const char *expected[] = {"python_program", "python_language", "programming_language"};
    for (size_t k = 0; k < 3; k++) {
        char *converted = camel_to_snake(input[k]);
        if (converted != NULL) {
            printf("%s: %s\n", strcmp(converted, expected[k]) == 0 ? "Passed" : "Failed", converted);
            free(converted);
        } else {
            printf("Conversion failed for input: %s\n", input[k]);
        }
    }
    return 0;
}