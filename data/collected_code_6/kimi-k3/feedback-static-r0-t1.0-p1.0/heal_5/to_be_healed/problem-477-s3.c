#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_INPUT_LEN 256

char *to_lowercase(const char *input, size_t max_len)
{
    char *result;
    size_t i;
    size_t len;

    if (input == NULL || max_len == 0)
    {
        return NULL;
    }

    len = strnlen(input, max_len);
    result = (char *)malloc(len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = (char)tolower((unsigned char)input[i]);
    }

    result[len] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN + 2];
    char *lowercase_str;
    size_t input_len;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input_len = strcspn(input, "\n");

    if (input[input_len] != '\n' && !feof(stdin))
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    input[input_len] = '\0';

    lowercase_str = to_lowercase(input, MAX_INPUT_LEN + 1);

    if (lowercase_str == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Lowercase string: %s\n", lowercase_str);

    free(lowercase_str);
    lowercase_str = NULL;

    return 0;
}