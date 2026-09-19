#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    concat = (char *)malloc(2 * len1 + 1);
    if (concat == NULL) {
        return 0;
    }

    memcpy(concat, str1, len1);
    memcpy(concat + len1, str1, len1);
    concat[2 * len1] = '\0';

    result = strstr(concat, str2) != NULL;

    free(concat);

    return result;
}

int main(void) {
    const char *s1 = "abcd";
    const char *s2 = "cdab";
    const char *s3 = "acbd";
    const char *s4 = NULL;
    const char *s5 = "abc";
    const char *s6 = "";

    printf("%s\n", areRotations(s1, s2) ? "True" : "False");
    printf("%s\n", areRotations(s1, s3) ? "True" : "False");
    printf("%s\n", areRotations(s1, s4) ? "True" : "False");
    printf("%s\n", areRotations(s1, s5) ? "True" : "False");
    printf("%s\n", areRotations(s6, s6) ? "True" : "False");

    return 0;
}