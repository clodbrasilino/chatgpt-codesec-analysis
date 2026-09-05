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

    if (space_count == 0) {
        char *copy = malloc(len + 1);
        if (copy == NULL) {
            return NULL;
        }
        strcpy(copy, str);
        return copy;
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
    (void)argc;
    (void)argv;

    const char *original = "Hello World ! This is a test .";
    char *replaced = replace_spaces(original);

    if (replaced != NULL) {
        printf("%s\n", replaced);
        free(replaced);
    }

    /* Possible weaknesses found:
     *  Calling function 'replace_spaces' returns 0
     *  Assignment 'null_test=replace_spaces(NULL)', assigned value is 0
     */
    char *null_test = replace_spaces(NULL);

    /* Possible weaknesses found:
     *  Condition 'null_test!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'null_test!=NULL' is always false
     */
    if (null_test != NULL) {
        printf("%s\n", null_test);
        free(null_test);
    } else {
        printf("NULL input handled.\n");
    }

    return 0;
}