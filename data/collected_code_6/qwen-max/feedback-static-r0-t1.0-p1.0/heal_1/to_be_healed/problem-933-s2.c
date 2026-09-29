#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

void camel_to_snake(const char *input, char *output) {
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(buffer, input);

    int nmatches = 1;
    while (nmatches > 0) {
        nmatches = regexec(&regex, buffer, 2, matches, 0);
        if (nmatches > 0) {
            buffer[matches[1].rm_so + 1] = '_';
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(&buffer[matches[1].rm_so + 2], &buffer[matches[1].rm_so + 1], strlen(&buffer[matches[1].rm_so + 1]));
            /* Possible weaknesses found:
             *  Array 'matches[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
             */
            buffer[matches[2].rm_so + 1] = buffer[matches[2].rm_so];
            /* Possible weaknesses found:
             *  Array 'matches[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
             */
            buffer[matches[2].rm_so] = buffer[matches[2].rm_so + 1];
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (int i = 0; i < strlen(buffer); ++i) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'tolower'
         *  call to undeclared library function 'tolower' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        buffer[i] = tolower(buffer[i]);
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(output, buffer);
    regfree(&regex);
}

int main() {
    const char *input = "camelCaseExample";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[1024];
    camel_to_snake(input, output);
    printf("%s\n", output);
    return 0;
}