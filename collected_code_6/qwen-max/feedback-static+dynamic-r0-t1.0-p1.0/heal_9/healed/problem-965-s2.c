#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    char *result = malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i]) && i > 0 && str[i - 1] != '_') {
            result[j++] = '_';
        }
        result[j++] = tolower((unsigned char)str[i]);
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *input[] = {"PythonProgram", "Python_Language", "ProgrammingLanguage"};
    const char *expected[] = {"python_program", "python_language", "programming_language"};
    for (size_t k = 0; k < 3; k++) {
        char *converted = camel_to_snake(input[k]);
        printf("%s: %s\n", converted != NULL && strcmp(converted, expected[k]) == 0 ? "Passed" : "Failed", converted);
        free(converted);
    }
    return 0;
}