#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *temp;
    size_t temp_size;
    int result;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 == 0 && len2 == 0) {
        return 1;
    }

    if (len1 == 0 || len2 == 0) {
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    temp_size = 2 * len1 + 1;
    temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return 0;
    }

    result = snprintf(temp, temp_size, "%s%s", str1, str1);
    if (result < 0 || (size_t)result >= temp_size) {
        free(temp);
        return 0;
    }

    if (strstr(temp, str2) != NULL) {
        free(temp);
        return 1;
    }

    free(temp);
    return 0;
}

int main(void) {
    const char *s1 = "rotation";
    const char *s2 = "tationro";
    const char *s3 = "rotations";
    const char *s4 = "hello";
    const char *s5 = "lohel";
    const char *s6 = "";
    const char *s7 = "";

    printf("'%s' and '%s': %s\n", s1, s2, are_rotations(s1, s2) ? "True" : "False");
    printf("'%s' and '%s': %s\n", s1, s3, are_rotations(s1, s3) ? "True" : "False");
    printf("'%s' and '%s': %s\n", s4, s5, are_rotations(s4, s5) ? "True" : "False");
    printf("'%s' and NULL: %s\n", s1, are_rotations(s1, NULL) ? "True" : "False");
    printf("'%s' and '%s': %s\n", s6, s7, are_rotations(s6, s7) ? "True" : "False");

    return 0;
}