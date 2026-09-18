#include <stdio.h>
#include <string.h>

char *rotate_string_left(char *str, size_t n) {
    size_t str_length = strlen(str);
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *result = malloc((str_length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < str_length; ++i) {
        size_t new_idx = (i + n) % str_length;
        result[i] = str[new_idx];
    }

    result[str_length] = '\0';

    return result;
}

int main(void) {
    char str[] = "Hello, world!";
    size_t n = 2;

    printf("Original string: %s\n", str);

    char *rotated = rotate_string_left(str, n);

    if (rotated == NULL) {
        return 1;
    }

    printf("Rotated string: %s\n", rotated);

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(rotated);

    return 0;
}