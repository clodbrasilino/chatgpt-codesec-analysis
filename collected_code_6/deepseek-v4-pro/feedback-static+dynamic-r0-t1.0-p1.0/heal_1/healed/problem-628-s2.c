#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t space_count = 0;
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_length = length + (space_count * 2);
    char *result = (char *)malloc((new_length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "My Name is Dawood",
        "I am a Programmer",
        "I love Coding"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *replaced = replace_spaces(test_cases[i]);
        if (replaced != NULL) {
            printf("%s\n", replaced);
            free(replaced);
        } else {
            printf("Memory allocation failed or input string is NULL\n");
        }
    }

    return 0;
}