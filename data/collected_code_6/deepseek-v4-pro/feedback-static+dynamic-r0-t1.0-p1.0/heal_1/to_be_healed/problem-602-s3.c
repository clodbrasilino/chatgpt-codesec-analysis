#include <stdio.h>
#include <string.h>
#include <limits.h>

char first_repeated_char(const char *str)
{
    int count[UCHAR_MAX + 1] = {0};
    size_t i;

    for (i = 0; str[i] != '\0'; i++) {
        count[(unsigned char)str[i]]++;
        if (count[(unsigned char)str[i]] == 2) {
            return str[i];
        }
    }

    return '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    char result;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    result = first_repeated_char(str);
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return 0;
}