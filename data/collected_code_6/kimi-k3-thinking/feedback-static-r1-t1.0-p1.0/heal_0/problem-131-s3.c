#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_vowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return true;
        default:
            return false;
    }
}

static int reverse_vowels(char *str)
{
    size_t left = 0;
    size_t right;

    if (str == NULL)
    {
        return -1;
    }

    right = strlen(str);

    while (left < right)
    {
        while (left < right && !is_vowel(str[left]))
        {
            left++;
        }
        while (left < right && !is_vowel(str[right - 1]))
        {
            right--;
        }
        if (left < right)
        {
            char temp = str[left];
            str[left] = str[right - 1];
            str[right - 1] = temp;
            left++;
            right--;
        }
    }

    return 0;
}

int main(void)
{
    char tests[][32] = {
        "Hello, World!",
        "Programming",
        "AEIOU",
        "rhythm",
        "aA",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++)
    {
        printf("Original:        \"%s\"\n", tests[i]);
        if (reverse_vowels(tests[i]) != 0)
        {
            fprintf(stderr, "Error: reverse_vowels failed for test %zu\n", i);
            return 1;
        }
        printf("Vowels reversed: \"%s\"\n", tests[i]);
    }

    return 0;
}