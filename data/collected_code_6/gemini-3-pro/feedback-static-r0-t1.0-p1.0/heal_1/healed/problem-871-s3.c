#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }
    
    size_t len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    size_t buffer_size = 2 * len1 + 1;
    char *temp = (char *)malloc(buffer_size);
    if (temp == NULL) {
        return 0;
    }

    snprintf(temp, buffer_size, "%s%s", str1, str1);

    int result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main(void) {
    const char *str1 = "waterbottle";
    const char *str2 = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}