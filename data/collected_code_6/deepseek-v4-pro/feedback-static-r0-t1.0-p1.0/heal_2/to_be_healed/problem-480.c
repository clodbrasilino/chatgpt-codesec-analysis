#include <stdio.h>
#include <string.h>
#include <limits.h>

char find_max_occurring_char(const char *str) {
    int count[UCHAR_MAX + 1] = {0};
    int len = strnlen(str, UCHAR_MAX + 1);
    char max_char = '\0';
    int max_count = 0;
    int i;

    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    for (i = 0; str[i] != '\0' && i < len; i++) {
        unsigned char ch = (unsigned char)str[i];
        count[ch]++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }

    return max_char;
}

int main(void) {
    const char str[] = "sample string with some characters";
    char result;

    result = find_max_occurring_char(str);
    printf("Max occurring character: %c\n", result);

    return 0;
}