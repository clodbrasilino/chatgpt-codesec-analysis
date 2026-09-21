#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;
    size_t concat_len;

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

    concat_len = 2 * len1;
    concat = (char *)malloc(concat_len + 1);
    if (concat == NULL) {
        return 0;
    }

    memcpy(concat, str1, len1);
    memcpy(concat + len1, str1, len1);
    concat[concat_len] = '\0';

    result = strstr(concat, str2) != NULL;

    free(concat);

    return result;
}

int main(void) {
    const char *s1 = "abcd";
    const char *s2 = "cdab";
    const char *s3 = "acbd";

    if (areRotations(s1, s2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (areRotations(s1, s3)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}