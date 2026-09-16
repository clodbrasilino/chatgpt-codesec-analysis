#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return 0;
    }

    concat = (char *)malloc(2 * len1 + 1);
    if (concat == NULL) {
        return 0;
    }

    memcpy(concat, str1, len1);
    memcpy(concat + len1, str1, len1);
    concat[2 * len1] = '\0';

    result = (strstr(concat, str2) != NULL);

    free(concat);
    concat = NULL;

    return result;
}

int main(void) {
    const char *str1 = "abcde";
    const char *str2 = "cdeab";
    const char *str3 = "abced";
    const char *str4 = "aaaaa";
    const char *str5 = "aaaaa";

    printf("%s\n", areRotations(str1, str2) ? "True" : "False");
    printf("%s\n", areRotations(str1, str3) ? "True" : "False");
    printf("%s\n", areRotations(str4, str5) ? "True" : "False");

    return 0;
}