#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2, int len) {
    int count01 = 0, count10 = 0;
    for (int i = 0; i < len; i++) {
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
     *  Assignment 'len1=strlen(str1)', assigned value is 4
     */
    int len1 = strlen(str1);
    int len2 = strlen(str2);

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