#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

int are_rotations(const char *s1, const char *s2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (s1 == NULL || s2 == NULL) {
        printf("False\n");
        return 0;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        printf("False\n");
        return 0;
    }

    if (len1 == 0) {
        printf("True\n");
        return 1;
    }

    concat = (char *)malloc(len1 * 2 + 1);
    if (concat == NULL) {
        printf("False\n");
        return 0;
    }

    memcpy(concat, s1, len1);
    memcpy(concat + len1, s1, len1);
    concat[len1 * 2] = '\0';

    result = (strstr(concat, s2) != NULL) ? 1 : 0;

    free(concat);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return result;
}

int main(int argc, char *argv[]) {
    const char *str1 = "abcd";
    const char *str2 = "cdab";
    const char *str3 = "acbd";
    const char *str4 = NULL;
    const char *str5 = "abc";
    const char *str6 = "";

    are_rotations(str1, str2);
    are_rotations(str1, str3);
    are_rotations(str4, str1);
    are_rotations(str1, str5);
    are_rotations(str6, str6);

    return 0;
}