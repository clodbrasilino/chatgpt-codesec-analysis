#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **remove_digits(char *strings[], size_t arr_size) {
    for (size_t i = 0; i < arr_size; ++i) {
        if (strings[i] == NULL) continue;

        char *write_ptr = strings[i];
        /* Possible weaknesses found:
         * ASan: SEGV
         */
        for (char *read_ptr = strings[i]; *read_ptr; ++read_ptr) {
            if (!isdigit((unsigned char)*read_ptr)) {
                *write_ptr++ = *read_ptr;
            }
        }
        *write_ptr = '\0';
    }

    return strings;
}

int main() {
    char strings[][16] = {"hello123", "world456", "example789", "test123"};
    size_t arr_size = sizeof(strings) / sizeof(strings[0]);

    remove_digits((char **)strings, arr_size);

    for (size_t i = 0; i < arr_size; ++i) {
        printf("%s\n", strings[i]);
    }

    return 0;
}