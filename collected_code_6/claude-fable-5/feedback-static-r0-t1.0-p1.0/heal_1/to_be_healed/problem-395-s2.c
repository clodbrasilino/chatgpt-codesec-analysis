#include <stdio.h>
#include <string.h>
#include <limits.h>

int first_non_repeated(const char *str)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    for (i = 0; i < len; i++) {
        if (counts[(unsigned char)str[i]] == 1) {
            return (int)(unsigned char)str[i];
        }
    }

    return -1;
}

int main(void)
{
    const char *test1 = "swiss";
    const char *test2 = "aabbcc";
    const char *test3 = "programming";
    int result;

    result = first_non_repeated(test1);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test1, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test1);
    }

    result = first_non_repeated(test2);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test2, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test2);
    }

    result = first_non_repeated(test3);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test3, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test3);
    }

    return 0;
}