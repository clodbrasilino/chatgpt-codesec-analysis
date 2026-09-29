#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToEqual(const char *s1, const char *s2, size_t len) {
    int count1_s1 = 0, count1_s2 = 0;
    int type1 = 0, type2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '1') count1_s1++;
        if (s2[i] == '1') count1_s2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') type1++;
            else type2++;
        }
    }

    if (count1_s1 != count1_s2) return -1;
    if (type1 % 2 != 0 || type2 % 2 != 0) return -1;

    return type1 / 2 + type2 / 2 + (type1 % 2) * 2;
}

char *read_string_safe(const char *prompt) {
    printf("%s", prompt);
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t len = getline(&buffer, &bufsize, stdin);
    if (len == -1) {
        free(buffer);
        return NULL;
    }
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    return buffer;
}

int main(void) {
    char *s1 = read_string_safe("Enter first binary string: ");
    if (!s1) return 1;

    char *s2 = read_string_safe("Enter second binary string: ");
    if (!s2) {
        free(s1);
        return 1;
    }

    size_t len1 = 0;
    while (s1[len1] != '\0') {
        if (s1[len1] != '0' && s1[len1] != '1') {
            printf("Strings must contain only '0' and '1' characters\n");
            free(s1);
            free(s2);
            return 1;
        }
        len1++;
    }

    size_t len2 = 0;
    while (s2[len2] != '\0') {
        if (s2[len2] != '0' && s2[len2] != '1') {
            printf("Strings must contain only '0' and '1' characters\n");
            free(s1);
            free(s2);
            return 1;
        }
        len2++;
    }

    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        free(s1);
        free(s2);
        return 1;
    }

    int result = minSwapsToEqual(s1, s2, len1);
    printf("Minimum swaps required: %d\n", result);

    free(s1);
    free(s2);
    return 0;
}