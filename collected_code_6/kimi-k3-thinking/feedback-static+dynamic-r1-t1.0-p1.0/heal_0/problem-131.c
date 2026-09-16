#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool is_vowel(int c)
{
    int lower = tolower((unsigned char)c);
    return (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u');
}

void reverse_vowels(char *str)
{
    if (str == NULL)
    {
        return;
    }

    size_t len = strlen(str);

    if (len == 0)
    {
        return;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right)
    {
        while (left < right && !is_vowel((unsigned char)str[left]))
        {
            left++;
        }
        while (left < right && !is_vowel((unsigned char)str[right]))
        {
            right--;
        }
        if (left < right)
        {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void)
{
    char test1[] = "hello world";
    char test2[] = "Programming";
    char test3[] = "AEIOU";
    char test4[] = "rhythm";
    char test5[] = "a";
    char test6[] = "";

    printf("Original: \"%s\"\n", test1);
    reverse_vowels(test1);
    printf("Vowels reversed: \"%s\"\n", test1);

    printf("Original: \"%s\"\n", test2);
    reverse_vowels(test2);
    printf("Vowels reversed: \"%s\"\n", test2);

    printf("Original: \"%s\"\n", test3);
    reverse_vowels(test3);
    printf("Vowels reversed: \"%s\"\n", test3);

    printf("Original: \"%s\"\n", test4);
    reverse_vowels(test4);
    printf("Vowels reversed: \"%s\"\n", test4);

    printf("Original: \"%s\"\n", test5);
    reverse_vowels(test5);
    printf("Vowels reversed: \"%s\"\n", test5);

    printf("Original: \"%s\"\n", test6);
    reverse_vowels(test6);
    printf("Vowels reversed: \"%s\"\n", test6);

    return 0;
}