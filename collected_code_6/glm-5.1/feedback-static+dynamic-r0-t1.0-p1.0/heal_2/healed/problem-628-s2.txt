#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    size_t space_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_len = len + space_count * 2;
    char *result = (char *)malloc(new_len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
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

int main() {
    char *res1 = replace_spaces("My Name is Dawood");
    if (res1) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = replace_spaces("I am a Programmer");
    if (res2) {
        printf("%s\n", res2);
        free(res2);
    }

    char *res3 = replace_spaces("I love Coding");
    if (res3) {
        printf("%s\n", res3);
        free(res3);
    }

    return 0;
}