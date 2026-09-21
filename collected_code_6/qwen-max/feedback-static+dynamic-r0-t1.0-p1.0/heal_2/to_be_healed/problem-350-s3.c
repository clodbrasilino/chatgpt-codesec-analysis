#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* minimize_string_length(const char *str, char ch) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            count++;
        }
    }
    if (count == 0) {
        return strdup(str);
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = (char*)malloc(strlen(str) - count + 1);
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ch) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "example string with some characters to remove";
    char ch = 'e';
    char *minimized_str = minimize_string_length(str, ch);
    if (minimized_str != NULL) {
        printf("Minimized string: %s\n", minimized_str);
        free(minimized_str);
    } else {
        printf("Error in minimizing the string.\n");
    }
    return 0;
}