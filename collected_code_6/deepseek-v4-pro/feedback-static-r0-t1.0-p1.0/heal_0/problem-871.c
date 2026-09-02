#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *temp;
    int result;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    temp = (char *)malloc(2 * len1 + 1);
    if (temp == NULL) {
        return 0;
    }

    strcpy(temp, str1);
    strcat(temp, str1);

    result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main(void) {
    const char *s1 = "rotation";
    const char *s2 = "tationro";
    const char *s3 = "rotations";
    const char *s4 = "hello";
    const char *s5 = "lohel";

    printf("'%s' and '%s': %s\n", s1, s2, are_rotations(s1, s2) ? "true" : "false");
    printf("'%s' and '%s': %s\n", s1, s3, are_rotations(s1, s3) ? "true" : "false");
    printf("'%s' and '%s': %s\n", s4, s5, are_rotations(s4, s5) ? "true" : "false");
    printf("'%s' and NULL: %s\n", s1, are_rotations(s1, NULL) ? "true" : "false");

    return 0;
}