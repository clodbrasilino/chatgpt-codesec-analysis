#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    size_t space_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_len = len + space_count * 2;
    char *new_str = malloc(new_len + 1);

    if (new_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            new_str[j++] = '%';
            new_str[j++] = '2';
            new_str[j++] = '0';
        } else {
            new_str[j++] = str[i];
        }
    }

    new_str[j] = '\0';
    return new_str;
}

int main(int argc, char *argv[]) {
    const char *original = "My Name is Dawood";
    char *replaced = replace_spaces(original);

    if (replaced != NULL) {
        printf("%s\n", replaced);
        free(replaced);
    }

    const char *test1 = "I am a Programmer";
    char *replaced1 = replace_spaces(test1);
    if (replaced1 != NULL) {
        printf("%s\n", replaced1);
        free(replaced1);
    }

    const char *test2 = "I love Coding";
    char *replaced2 = replace_spaces(test2);
    if (replaced2 != NULL) {
        printf("%s\n", replaced2);
        free(replaced2);
    }

    char *null_result = replace_spaces(NULL);
    if (null_result == NULL) {
        printf("NULL input handled.\n");
    }

    return 0;
}