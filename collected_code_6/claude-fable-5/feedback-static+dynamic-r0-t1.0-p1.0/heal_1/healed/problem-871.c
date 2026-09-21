#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t temp_size;
    char *temp;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = strnlen(s1, MAX_STR_LEN);
    len2 = strnlen(s2, MAX_STR_LEN);

    if (len1 >= MAX_STR_LEN || len2 >= MAX_STR_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    temp_size = 2 * len1 + 1;
    temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    memcpy(temp, s1, len1);
    memcpy(temp + len1, s1, len1);
    temp[temp_size - 1] = '\0';

    result = (strstr(temp, s2) != NULL) ? 1 : 0;

    free(temp);
    return result;
}

int main(void)
{
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";
    const char *str3 = "ACBD";
    int res;

    res = are_rotations(str1, str2);
    if (res < 0) {
        fprintf(stderr, "Error: allocation failure or input too long\n");
        return EXIT_FAILURE;
    }
    printf("\"%s\" and \"%s\": %s\n", str1, str2,
           (res == 1) ? "rotations" : "not rotations");

    res = are_rotations(str1, str3);
    if (res < 0) {
        fprintf(stderr, "Error: allocation failure or input too long\n");
        return EXIT_FAILURE;
    }
    printf("\"%s\" and \"%s\": %s\n", str1, str3,
           (res == 1) ? "rotations" : "not rotations");

    return EXIT_SUCCESS;
}