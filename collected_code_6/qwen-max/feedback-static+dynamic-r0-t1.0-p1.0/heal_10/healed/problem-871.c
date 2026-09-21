#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool safe_strlen(const char *str, size_t *len) {
    if (str == NULL) return false;
    for (*len = 0; str[*len]; (*len)++);
    return true;
}

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) return false;

    size_t len1, len2;
    if (!safe_strlen(str1, &len1) || !safe_strlen(str2, &len2)) return false;

    if (len1 != len2) return false;

    if (len1 > INT_MAX / 2) return false;

    char *temp = (char *)malloc((len1 * 2 + 1) * sizeof(char));
    if (temp == NULL) return false;

    snprintf(temp, (len1 * 2 + 1), "%.*s%.*s", (int)len1, str1, (int)len1, str1);

    int result = strstr(temp, str2) != NULL;
    free(temp);
    return result;
}

int main() {
    const char str1[] = "waterbottle";
    const char str2[] = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}