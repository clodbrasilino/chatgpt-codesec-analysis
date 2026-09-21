#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

size_t safe_strlen(const char *str) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < MAX_STR_LEN) {
        len++;
    }
    return len;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = safe_strlen(str1);
    size_t len2 = safe_strlen(str2);

    if (len1 != len2 || len1 == 0 || len1 == MAX_STR_LEN) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len1 + 1);
    if (temp == NULL) {
        return 0;
    }

    snprintf(temp, 2 * len1 + 1, "%s%s", str1, str1);

    int result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main(void) {
    const char *str1 = "waterbottle";
    const char *str2 = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}