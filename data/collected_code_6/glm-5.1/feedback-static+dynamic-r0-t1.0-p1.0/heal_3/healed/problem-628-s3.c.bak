#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t space_count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_len = len + space_count * 2;
    char *new_str = (char*)malloc(new_len + 1);

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
    
    printf("%s\n", new_str);

    return new_str;
}

int main(int argc, char *argv[]) {
    const char *test_cases[] = {
        "My Name is Dawood",
        "I am a Programmer",
        "I love Coding"
    };

    for (int i = 0; i < 3; i++) {
        char *replaced = replace_spaces(test_cases[i]);
        if (replaced != NULL) {
            free(replaced);
        }
    }

    const char *null_test = replace_spaces(NULL);
    if (null_test == NULL) {
        printf("NULL input handled.\n");
    }

    return 0;
}