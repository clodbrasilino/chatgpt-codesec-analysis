#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 4096

int findMinimumRotations(const char* str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Either the condition 'len==4096' is redundant or the array 'str[4]' is accessed at index 4096, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     *  Array index out of bounds
     */
    while (str[len] != '\0' && len < MAX_STR_LEN) {
        len++;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'len==4096' is not redundant
     */
    if (len == 0 || len == MAX_STR_LEN) {
        return 0;
    }

    for (size_t i = 1; i <= len; i++) {
        int match = 1;
        for (size_t j = 0; j < len; j++) {
            if (str[(i + j) % len] != str[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return (int)i;
        }
    }

    return (int)len;
}

int main(void) {
    const char* str1 = "abc";
    int result1 = findMinimumRotations(str1);
    printf("%d\n", result1);

    const char* str2 = "aaaa";
    int result2 = findMinimumRotations(str2);
    printf("%d\n", result2);

    const char* str3 = "abab";
    int result3 = findMinimumRotations(str3);
    printf("%d\n", result3);

    return 0;
}