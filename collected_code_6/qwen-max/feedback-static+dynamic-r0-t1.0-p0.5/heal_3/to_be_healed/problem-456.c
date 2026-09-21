#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(const char **list, int count) {
    if (list == NULL || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            char *temp_str = malloc((len + 1) * sizeof(char));
            if (temp_str == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(temp_str, list[i]);
            reverse_string(temp_str, len);
            const char *original = list[i];
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  Code 'C++ cast <...' is invalid C code. Use --std or --language to configure the language. [syntaxError]
             *  expected expression
             *  expected expression before 'char'
             *  use of undeclared identifier 'const_cast'
             *  'const_cast' undeclared (first use in this function)
             */
            *const_cast<char **>(&list[i]) = temp_str;
            free((void *)original);
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}