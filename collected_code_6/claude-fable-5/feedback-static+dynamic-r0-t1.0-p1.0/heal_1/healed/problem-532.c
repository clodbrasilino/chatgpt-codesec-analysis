#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LEN 4096

bool are_permutations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long counts[UCHAR_MAX + 1] = {0};

    if (s1 == NULL || s2 == NULL)
    {
        return false;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN)
    {
        return false;
    }

    if (len1 != len2)
    {
        return false;
    }

    for (i = 0; i < len1; i++)
    {
        counts[(unsigned char)s1[i]]++;
        counts[(unsigned char)s2[i]]--;
    }

    for (i = 0; i <= UCHAR_MAX; i++)
    {
        if (counts[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *a = "listen";
    const char *b = "silent";
    const char *c = "hello";

    if (are_permutations(a, b))
    {
        printf("\"%s\" and \"%s\" are permutations of each other.\n", a, b);
    }
    else
    {
        printf("\"%s\" and \"%s\" are not permutations of each other.\n", a, b);
    }

    if (are_permutations(a, c))
    {
        printf("\"%s\" and \"%s\" are permutations of each other.\n", a, c);
    }
    else
    {
        printf("\"%s\" and \"%s\" are not permutations of each other.\n", a, c);
    }

    return 0;
}