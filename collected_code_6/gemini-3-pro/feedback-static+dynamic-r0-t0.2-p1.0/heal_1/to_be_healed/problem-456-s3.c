#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t i = 0;
    size_t j = len - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void reverse_string_list(char **string_list, size_t count) {
    if (string_list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        reverse_string(string_list[i]);
    }
}

int main(void) {
    size_t count = 3;
    char **string_list = malloc(count * sizeof(char *));
    if (string_list == NULL) {
        return 1;
    }

    string_list[0] = strdup("Hello");
    string_list[1] = strdup("World");
    string_list[2] = strdup("C Programming");

    for (size_t i = 0; i < count; i++) {
        if (string_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(string_list[j]);
            }
            free(string_list);
            return 1;
        }
    }

    reverse_string_list(string_list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", string_list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(string_list[i]);
    }
    free(string_list);

    return 0;
}