#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool all_chars_same(const char *str)
{
    size_t len;
    size_t i;
    char first;

    if (str == NULL)
    {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0)
    {
        return false;
    }

    first = str[0];
    for (i = 1; i < len; i++)
    {
        if (str[i] != first)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *test1 = "aaaa";
    const char *test2 = "aaab";
    const char *test3 = "";
    const char *test4 = "x";

    printf("Test 1 (\"aaaa\"): %s\n", all_chars_same(test1) ? "true" : "false");
    printf("Test 2 (\"aaab\"): %s\n", all_chars_same(test2) ? "true" : "false");
    printf("Test 3 (\"\"): %s\n", all_chars_same(test3) ? "true" : "false");
    printf("Test 4 (\"x\"): %s\n", all_chars_same(test4) ? "true" : "false");

    return 0;
}