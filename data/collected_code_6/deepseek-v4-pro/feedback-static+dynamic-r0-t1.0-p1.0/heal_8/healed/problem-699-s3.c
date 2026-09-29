#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s1, const char *s2) {
    size_t len1, len2;
    int count1_0, count1_1;
    int count2_0, count2_1;
    int mismatch_0_to_1, mismatch_1_to_0;
    size_t i;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strnlen(s1, 101);
    len2 = strnlen(s2, 101);

    if (len1 != len2 || len1 == 0 || len1 > 100) {
        return -1;
    }

    count1_0 = 0;
    count1_1 = 0;
    count2_0 = 0;
    count2_1 = 0;

    for (i = 0; i < len1; i++) {
        if (s1[i] == '0') count1_0++;
        else if (s1[i] == '1') count1_1++;
        else return -1;

        if (s2[i] == '0') count2_0++;
        else if (s2[i] == '1') count2_1++;
        else return -1;
    }

    if (count1_0 != count2_0 || count1_1 != count2_1) {
        return -1;
    }

    mismatch_0_to_1 = 0;
    mismatch_1_to_0 = 0;

    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' && s2[i] == '1') {
                mismatch_0_to_1++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                mismatch_1_to_0++;
            }
        }
    }

    if (mismatch_0_to_1 != mismatch_1_to_0) {
        return -1;
    }

    return mismatch_0_to_1;
}

int main(void) {
    char str1[102];
    char str2[102];
    char *res1, *res2;
    size_t len1, len2;
    int result;

    res1 = fgets(str1, sizeof(str1), stdin);
    if (res1 == NULL) {
        printf("Not Possible\n");
        return 0;
    }

    len1 = strnlen(str1, sizeof(str1));
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }
    if (len1 > 100 || len1 == 0) {
        printf("Not Possible\n");
        return 0;
    }

    res2 = fgets(str2, sizeof(str2), stdin);
    if (res2 == NULL) {
        printf("Not Possible\n");
        return 0;
    }

    len2 = strnlen(str2, sizeof(str2));
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }
    if (len2 > 100 || len2 == 0) {
        printf("Not Possible\n");
        return 0;
    }

    result = min_swaps(str1, str2);

    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}