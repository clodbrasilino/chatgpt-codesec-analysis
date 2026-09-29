#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

size_t safe_strlen(const char *str) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'len<4096' is not redundant
     *  Either the condition 'len<4096' is redundant or the array 'str[12]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (len < MAX_STR_LEN && str[len] != '\0') {
        len++;
    }
    return len;
}

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = safe_strlen(str1);
    size_t len2 = safe_strlen(str2);

    if (len1 != len2 || len1 == 0 || len1 >= MAX_STR_LEN) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len1 + 1);
    if (temp == NULL) {
        return 0;
    }

    snprintf(temp, 2 * len1 + 1, "%s%s", str1, str1);

    int result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main(void) {
    const char *str1 = "waterbottle";
    const char *str2 = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}