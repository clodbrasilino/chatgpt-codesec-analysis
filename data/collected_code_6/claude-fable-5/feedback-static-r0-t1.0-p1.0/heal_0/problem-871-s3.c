#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    char *temp;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    temp = malloc((2 * len1) + 1);
    if (temp == NULL) {
        return -1;
    }

    memcpy(temp, s1, len1);
    memcpy(temp + len1, s1, len1);
    temp[2 * len1] = '\0';

    result = (strstr(temp, s2) != NULL) ? 1 : 0;

    free(temp);
    return result;
}

int main(void)
{
    const char *str1 = "ABCDE";
    const char *str2 = "CDEAB";
    const char *str3 = "ABDCE";
    int res;

    res = are_rotations(str1, str2);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (res == 1) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str2);
    }

    res = are_rotations(str1, str3);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (res == 1) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str3);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str3);
    }

    return EXIT_SUCCESS;
}