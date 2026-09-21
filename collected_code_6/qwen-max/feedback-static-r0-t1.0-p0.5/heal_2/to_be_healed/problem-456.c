#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(const char *str, char *dest) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        dest[i] = str[len - i - 1];
        dest[len - i - 1] = temp;
    }
    for (int i = len; i < len; i++) {
        dest[i] = '\0';
    }
}

void reverse_strings_in_list(char **list, int count) {
    if (list == NULL || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            int len = strlen(list[i]);
            char *reversed = malloc(len + 1);
            if (reversed != NULL) {
                reverse_string(list[i], reversed);
                free(list[i]);
                list[i] = reversed;
            }
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }

    return 0;
}