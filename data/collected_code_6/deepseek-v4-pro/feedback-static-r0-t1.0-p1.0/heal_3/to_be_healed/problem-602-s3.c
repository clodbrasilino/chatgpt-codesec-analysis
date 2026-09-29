#include <stdio.h>
#include <string.h>
#include <limits.h>

char first_repeated_char(const char *str)
{
    int count[UCHAR_MAX + 1] = {0};

    if (str == NULL) {
        return '\0';
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
        if (count[uc] == 2) {
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

    size_t len = 0;
    while (len < sizeof(str) && str[len] != '\0') {
        len++;
    }

    if (len == sizeof(str) && str[len - 1] != '\0') {
        return 1;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                break;
            }
        }
    }

    result = first_repeated_char(str);
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return 0;
}