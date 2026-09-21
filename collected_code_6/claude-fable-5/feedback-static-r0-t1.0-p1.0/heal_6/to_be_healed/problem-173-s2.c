#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096

char *remove_non_alnum(char *str, size_t max_len);

char *remove_non_alnum(char *str, size_t max_len)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t write;
    size_t len;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return NULL;
    }

    write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (read = 0; read < len && read < max_len; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (isalnum((unsigned char)str[read])) {
            if (write < max_len - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                str[write] = str[read];
                write++;
            }
        }
    }

    if (write < max_len) {
        str[write] = '\0';
    } else {
        return NULL;
    }

    return str;
}

int main(void)
{
    char input[] = "Hello, World! 123 #$%^ test_case-42";
    char *result;

    if (sizeof(input) > MAX_INPUT_LEN) {
        if (fprintf(stderr, "Error: input exceeds maximum length\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = remove_non_alnum(input, sizeof(input));
    if (result == NULL) {
        if (fprintf(stderr, "Error: invalid input string\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Result: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}