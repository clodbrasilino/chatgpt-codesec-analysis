#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countOddRotations(const char *s)
{
    size_t len;
    size_t i;
    int count;

    if (s == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);
    if (len == 0U)
    {
        return -1;
    }

    count = 0;
    for (i = 0U; i < len; i++)
    {
        if (s[i] == '1')
        {
            count++;
        }
        else if (s[i] != '0')
        {
            return -1;
        }
    }

    return count;
}

int main(void)
{
    const char *tests[] = { "011001", "11011", "0000", "1", "101" };
    size_t numTests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < numTests; i++)
    {
        int result = countOddRotations(tests[i]);
        if (result < 0)
        {
            if (fprintf(stderr, "Invalid input: %s\n", tests[i]) < 0)
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (printf("String: %s -> Odd rotations: %d\n", tests[i], result) < 0)
            {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}