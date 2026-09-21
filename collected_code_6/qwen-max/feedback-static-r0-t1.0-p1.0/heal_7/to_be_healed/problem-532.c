#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    if (len1 != len2) {
        return 0;
    }
    int count[256] = {0};
    for (size_t i = 0; i < len1; ++i) {
        /* Possible weaknesses found:
         *  Condition 'str2[i]=='\0'' is always false [knownConditionTrueFalse]
         *  Condition 'str1[i]=='\0'' is always false [knownConditionTrueFalse]
         */
        if (str1[i] == '\0' || str2[i] == '\0') {
            return 0;
        }
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    const char *str1 = "abc";
    const char *str2 = "cba";
    if (are_permutations(str1, str2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}