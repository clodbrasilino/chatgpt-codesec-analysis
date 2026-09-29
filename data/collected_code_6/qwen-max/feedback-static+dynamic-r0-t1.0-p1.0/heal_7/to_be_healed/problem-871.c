#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool safe_strlen(const char *str, size_t max_len, size_t *len) {
    if (str == NULL) return false;
    for (*len = 0; *len < max_len && str[*len]; (*len)++);
    return true;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1, len2;
    if (!safe_strlen(str1, SIZE_MAX, &len1) || !safe_strlen(str2, SIZE_MAX, &len2)) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[len1 * 2 + 1];
    snprintf(temp, sizeof(temp), "%s%s", str1, str1);

    return strstr(temp, str2) != NULL;
}

int main() {
    const char str1[] = "waterbottle";
    const char str2[] = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}