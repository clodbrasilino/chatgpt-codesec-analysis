#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);

    if (len1 != len2 || len1 == 0)
    {
        return 0;
    }

    if (len1 > (SIZE_MAX - 1) / 2)
    {
        return 0;
    }

    size_t concatLen = len1 * 2 + 1;
    char *concat = (char *)malloc(concatLen);
    if (concat == NULL)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat, str1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat + len1, str1, len1);
    concat[concatLen - 1] = '\0';

    int result = (strstr(concat, str2) != NULL);

    free(concat);
    concat = NULL;

    return result;
}

int main(void)
{
    const char *str1 = "abcde";
    const char *str2 = "cdeab";

    if (areRotations(str1, str2))
    {
        printf("The strings are rotations of each other.\n");
    }
    else
    {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}