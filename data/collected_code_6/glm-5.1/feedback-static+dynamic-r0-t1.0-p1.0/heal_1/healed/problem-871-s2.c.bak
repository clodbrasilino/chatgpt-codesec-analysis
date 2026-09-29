#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (str1 == NULL || str2 == NULL) {
        printf("False\n");
        return 0;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2) {
        printf("False\n");
        return 0;
    }

    if (len1 == 0) {
        printf("True\n");
        return 1;
    }

    concat = (char *)malloc(2 * len1 + 1);
    if (concat == NULL) {
        printf("False\n");
        return 0;
    }

    memcpy(concat, str1, len1);
    memcpy(concat + len1, str1, len1);
    concat[2 * len1] = '\0';

    result = strstr(concat, str2) != NULL;

    free(concat);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return result;
}

int main(void) {
    const char *s1 = "abcd";
    const char *s2 = "cdab";
    const char *s3 = "acbd";

    areRotations(s1, s2);
    areRotations(s1, s3);

    return 0;
}