#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_STRING_LENGTH 100

static int minSwapsToEqual(const char *s1, const char *s2, size_t len) {
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

static int validate_and_trim(char *str, size_t size, const char *input_name) {
    size_t len = strcspn(str, "\n");
    if (len < size && str[len] == '\n') {
        str[len] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        if (size > 0) {
            str[size - 1] = '\0';
        }
        printf("Warning: %s was truncated to %zu characters\n", input_name, size - 1);
    }
    return 0;
}

static int is_valid_binary(const char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[MAX_STRING_LENGTH + 4];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[MAX_STRING_LENGTH + 4];

    printf("Enter first binary string: ");
    if (fgets(s1, sizeof(s1), stdin) == NULL) return 1;
    validate_and_trim(s1, sizeof(s1), "first string");

    printf("Enter second binary string: ");
    if (fgets(s2, sizeof(s2), stdin) == NULL) return 1;
    validate_and_trim(s2, sizeof(s2), "second string");

    size_t len1 = strnlen(s1, MAX_STRING_LENGTH + 1);
    size_t len2 = strnlen(s2, MAX_STRING_LENGTH + 1);

    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    if (len1 == 0) {
        printf("Minimum swaps required: 0\n");
        return 0;
    }

    if (len1 > MAX_STRING_LENGTH) {
        printf("String length exceeds maximum allowed\n");
        return 1;
    }

    if (!is_valid_binary(s1, len1)) {
        printf("Invalid character in first string\n");
        return 1;
    }
    if (!is_valid_binary(s2, len2)) {
        printf("Invalid character in second string\n");
        return 1;
    }

    int result = minSwapsToEqual(s1, s2, len1);
    if (result == -1) {
        printf("Cannot make strings equal\n");
        return 1;
    }
    printf("Minimum swaps required: %d\n", result);

    return 0;
}