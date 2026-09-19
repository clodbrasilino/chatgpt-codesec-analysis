#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
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

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("false\n");
        return 1;
    }

    printf("%s\n", all_chars_same(argv[1]) ? "true" : "false");

    return 0;
}