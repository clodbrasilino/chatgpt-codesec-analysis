#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *s1, const char *s2, size_t len) {
    int count1 = 0, count2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int pos1 = 0, pos2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') pos1++;
            else pos2++;
        }
    }

    if (pos1 % 2 == 0 && pos2 % 2 == 0) {
        return pos1 / 2 + pos2 / 2;
    } else if (pos1 % 2 == 1 && pos2 % 2 == 1) {
        return pos1 / 2 + pos2 / 2 + 2;
    }

    return -1;
}

int main(void) {
    char *s1 = NULL;
    char *s2 = NULL;
    size_t bufsize = 256;
    ssize_t len1, len2;

    s1 = (char *)malloc(bufsize);
    if (s1 == NULL) {
        printf("-1\n");
        return 0;
    }

    s2 = (char *)malloc(bufsize);
    if (s2 == NULL) {
        free(s1);
        printf("-1\n");
        return 0;
    }

    printf("Enter first binary string: ");
    len1 = getline(&s1, &bufsize, stdin);
    if (len1 == -1) {
        free(s1);
        free(s2);
        printf("-1\n");
        return 0;
    }
    if (len1 > 0 && s1[len1 - 1] == '\n') {
        s1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter second binary string: ");
    len2 = getline(&s2, &bufsize, stdin);
    if (len2 == -1) {
        free(s1);
        free(s2);
        printf("-1\n");
        return 0;
    }
    if (len2 > 0 && s2[len2 - 1] == '\n') {
        s2[len2 - 1] = '\0';
        len2--;
    }

    if (len1 != len2 || len1 > 100 || len1 == 0) {
        free(s1);
        free(s2);
        printf("-1\n");
        return 0;
    }

    for (size_t i = 0; i < (size_t)len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            free(s1);
            free(s2);
            printf("-1\n");
            return 0;
        }
    }

    int result = minSwaps(s1, s2, (size_t)len1);
    printf("%d\n", result);

    free(s1);
    free(s2);

    return 0;
}