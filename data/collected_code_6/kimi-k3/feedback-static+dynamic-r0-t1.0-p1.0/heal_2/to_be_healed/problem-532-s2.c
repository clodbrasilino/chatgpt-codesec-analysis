#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CHAR_SET_SIZE 256
#define BUFFER_SIZE 256

bool are_permutations(const char *str1, const char *str2)
{
    int count[CHAR_SET_SIZE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = strnlen(str1, BUFFER_SIZE);
    len2 = strnlen(str2, BUFFER_SIZE);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (i = 0; i < CHAR_SET_SIZE; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[BUFFER_SIZE];
    int result;

    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    result = are_permutations(str1, str2);

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return EXIT_SUCCESS;
}