#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(const char **list, int count) {
    if (list == NULL || count <= 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = 0;
            const char *p = list[i];
            while (*p++) len++;
            char *temp_str = malloc(len + 1);
            if (temp_str == NULL) {
                return;
            }
            /* Possible weaknesses found:
             *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
             *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            strncpy(temp_str, list[i], len);
            temp_str[len] = '\0';
            reverse_string(temp_str, len);
            printf("%s\n", temp_str);
            free(temp_str);
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    return 0;
}