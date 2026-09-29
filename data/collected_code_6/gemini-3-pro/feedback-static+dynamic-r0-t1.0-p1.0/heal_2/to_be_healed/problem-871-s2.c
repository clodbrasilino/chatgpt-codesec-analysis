#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len1==4096' is redundant or the array 'str1[5]' is accessed at index 4096, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index 'len1' is used before limits check. [arrayIndexThenCheck]
     */
    while (str1[len1] != '\0' && len1 < MAX_STR_LEN) {
        len1++;
    }

    size_t len2 = 0;
    /* Possible weaknesses found:
     *  Array index 'len2' is used before limits check. [arrayIndexThenCheck]
     */
    while (str2[len2] != '\0' && len2 < MAX_STR_LEN) {
        len2++;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'len1==4096' is not redundant
     */
    if (len1 != len2 || len1 == 0 || len1 == MAX_STR_LEN) {
        return false;
    }

    size_t concatLen = len1 * 2 + 1;
    char *temp = (char *)malloc(concatLen);
    if (temp == NULL) {
        return false;
    }

    snprintf(temp, concatLen, "%s%s", str1, str1);

    bool isRotation = (strstr(temp, str2) != NULL);

    free(temp);

    return isRotation;
}

int main(void) {
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}