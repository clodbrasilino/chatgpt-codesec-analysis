#include <stdio.h>
#include <string.h>

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

int main(void) {
    char s1[101] = {0};
    char s2[101] = {0};

    printf("Enter first binary string: ");
    if (fgets(s1, sizeof(s1), stdin) == NULL) return 1;
    s1[strcspn(s1, "\n")] = '\0';

    printf("Enter second binary string: ");
    if (fgets(s2, sizeof(s2), stdin) == NULL) return 1;
    s2[strcspn(s2, "\n")] = '\0';

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    if (len1 == 0) {
        printf("Minimum swaps required: 0\n");
        return 0;
    }

    int result = minSwapsToEqual(s1, s2, len1);
    printf("Minimum swaps required: %d\n", result);

    return 0;
}