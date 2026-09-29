#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_pattern(const char *str, size_t len) {
    if (len < 3 || len > 4) return false;
    if (str[0] != 'a') return false;
    int b_count = 0;
    for (size_t i = 1; i < len; ++i) {
        if (str[i] == 'b') b_count++;
        else return false;
    }
    return b_count >= 2 && b_count <= 3;
}

int main() {
    const char *test1 = "abb";
    const char *test2 = "abbb";
    const char *test3 = "a";
    const char *test4 = "abbbb";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test1, matches_pattern(test1, strlen(test1)) ? "Match" : "No Match");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test2, matches_pattern(test2, strlen(test2)) ? "Match" : "No Match");
    /* Possible weaknesses found:
     *  Condition 'matches_pattern(test3,strlen(test3))' is always false [knownConditionTrueFalse]
     *  Condition 'matches_pattern(test3,strlen(test3))' is always false
     *  Calling function 'matches_pattern' returns 0
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test3, matches_pattern(test3, strlen(test3)) ? "Match" : "No Match");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'matches_pattern(test4,strlen(test4))' is always false
     *  Calling function 'matches_pattern' returns 0
     *  Condition 'matches_pattern(test4,strlen(test4))' is always false [knownConditionTrueFalse]
     */
    printf("%s: %s\n", test4, matches_pattern(test4, strlen(test4)) ? "Match" : "No Match");

    return 0;
}