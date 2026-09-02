#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Possible weaknesses found:
 *  Parameter 'arr_size' can be declared as pointer to const [constParameterPointer]
 */
char **remove_digits(char **strings, size_t *arr_size) {
    for (size_t i = 0; i < *arr_size; ++i) {
        if (strings[i] == NULL) continue;

        char *write_ptr = strings[i];
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
    char *strings[] = {"hello123", "world456", "example789", "test123", NULL};
    size_t arr_size = 4; // The number of strings

    /* Possible weaknesses found:
     *  assignment to expression with array type
     *  array type 'char *[5]' is not assignable
     */
    strings = remove_digits(strings, &arr_size);

    for (size_t i = 0; i < arr_size; ++i) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < arr_size; ++i) {
        free(strings[i]);
    }
    /* Possible weaknesses found:
     *  Deallocation of an auto-variable results in undefined behaviour. [autovarInvalidDeallocation]
     */
    free(strings);

    return 0;
}