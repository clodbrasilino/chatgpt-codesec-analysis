#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, 101);
    size_t len2 = strnlen(str2, 101);

    if (len1 >= 101 || len2 >= 101) {
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    size_t temp_size = 2 * len1 + 1;
    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return 0;
    }

    size_t copied = 0;
    for (size_t i = 0; i < len1 && copied < temp_size - 1; i++) {
        temp[copied++] = str1[i];
    }
    for (size_t i = 0; i < len1 && copied < temp_size - 1; i++) {
        temp[copied++] = str1[i];
    }
    temp[copied] = '\0';

    int result = (strstr(temp, str2) != NULL);

    free(temp);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[101] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[101] = {0};

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    if (strnlen(str1, 101) >= 101) {
        return 1;
    }

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    if (strnlen(str2, 101) >= 101) {
        return 1;
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}