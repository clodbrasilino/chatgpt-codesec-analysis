#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2, size_t len) {
    int count01 = 0, count10 = 0;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] == '0' && str2[i] == '1') {
            count01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count10++;
        }
    }
    return (count01 + 1) / 2 + (count10 + 1) / 2;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'str1="1100"', assigned value is "1100"
     */
    const char *str1 = "1100";
    const char *str2 = "0011";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assignment 'len1=strlen(str1)', assigned value is 4
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);

    /* Possible weaknesses found:
     *  Condition 'len1!=len2' is always false
     *  Condition 'len1!=len2' is always false [knownConditionTrueFalse]
     */
    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    int swaps = min_swaps(str1, str2, len1);
    printf("Minimum number of swaps: %d\n", swaps);
    return 0;
}