#include <stdio.h>
#include <ctype.h>

int count_vowels(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str) {
        char c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "AEIOUaeiou";
    const char *test3 = "bcdfghjklmnpqrstvwxyz";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("Vowels in \"%s\": %d\n", test1, count_vowels(test1));
    printf("Vowels in \"%s\": %d\n", test2, count_vowels(test2));
    printf("Vowels in \"%s\": %d\n", test3, count_vowels(test3));
    printf("Vowels in \"%s\": %d\n", test4, count_vowels(test4));
    printf("Vowels in NULL: %d\n", count_vowels(test5));

    return 0;
}