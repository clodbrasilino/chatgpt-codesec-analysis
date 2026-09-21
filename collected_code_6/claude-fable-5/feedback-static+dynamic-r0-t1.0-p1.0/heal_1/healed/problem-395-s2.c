#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 4096

int first_non_repeated(const char *str, size_t max_len)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);

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

    result = first_non_repeated(test1, MAX_INPUT_LEN);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test1, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test1);
    }

    result = first_non_repeated(test2, MAX_INPUT_LEN);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test2, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test2);
    }

    result = first_non_repeated(test3, MAX_INPUT_LEN);
    if (result >= 0) {
        printf("First non-repeated character in \"%s\": %c\n", test3, (char)result);
    } else {
        printf("No non-repeated character found in \"%s\"\n", test3);
    }

    return 0;
}