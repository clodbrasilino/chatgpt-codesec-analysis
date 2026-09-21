#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

char *snake_to_camel(const char *snake)
{
    const unsigned char *source;
    size_t output_length = 0;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source != (unsigned char)'_') {
            if (output_length == SIZE_MAX - 1) {
                return NULL;
            }
            ++output_length;
        }
        ++source;
    }

    camel = malloc(output_length + 1);
    if (camel == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source == (unsigned char)'_') {
            capitalize_next = 1;
        } else {
            camel[destination_index++] = capitalize_next
                ? (char)toupper(*source)
                : (char)*source;
            capitalize_next = 0;
        }
        ++source;
    }

    camel[destination_index] = '\0';
    return camel;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *camel;
    int result;

    if (argc == 2 && argv != NULL && argv[1] != NULL) {
        camel = snake_to_camel(argv[1]);
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char input[4096];

        if (fgets(input, sizeof input, stdin) == NULL) {
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
         *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        input[strcspn(input, "\r\n")] = '\0';
        camel = snake_to_camel(input);
    }

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    result = puts(camel);
    free(camel);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}