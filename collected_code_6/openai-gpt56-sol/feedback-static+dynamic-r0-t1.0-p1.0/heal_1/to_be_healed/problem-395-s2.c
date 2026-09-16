#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_first_non_repeated(const char *string, unsigned char *result)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *cursor;

    if (string == NULL || result == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        ++frequencies[*cursor];
        ++cursor;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        if (frequencies[*cursor] == 1) {
            *result = *cursor;
            return 1;
        }
        ++cursor;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    unsigned char result;
    int status;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    status = find_first_non_repeated(input, &result);

    if (status < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (status == 1) {
        if (printf("%c\n", result) < 0) {
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No non-repeated character found.") == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);
    return EXIT_SUCCESS;
}