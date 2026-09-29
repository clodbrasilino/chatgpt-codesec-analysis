#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  expected 'const char *' but argument is of type 'const char **'
 */
bool matches_pattern(const char *str, size_t len) {
    if (len < 3 || len > 4) {
        return false;
    }
    if (str[0] != 'a') {
        return false;
    }
    int b_count = 0;
    for (size_t i = 1; i < len; ++i) {
        if (str[i] == 'b') {
            b_count++;
        } else {
            return false;
        }
    }
    return b_count >= 2 && b_count <= 3;
}

int main() {
    /* Possible weaknesses found:
     *  invalid initializer
     *  array initializer must be an initializer list
     */
    const char *test1[] = "abb";
    /* Possible weaknesses found:
     *  invalid initializer
     *  array initializer must be an initializer list
     */
    const char *test2[] = "abbb";
    /* Possible weaknesses found:
     *  invalid initializer
     *  array initializer must be an initializer list
     */
    const char *test3[] = "a";
    /* Possible weaknesses found:
     *  invalid initializer
     *  array initializer must be an initializer list
     */
    const char *test4[] = "abbbb";

    /* Possible weaknesses found:
     *  passing argument 1 of 'matches_pattern' from incompatible pointer type [-Wincompatible-pointer-types]
     *  invalid application of 'sizeof' to an incomplete type 'const char *[]'
     */
    printf("%s: %s\n", test1, matches_pattern(test1, sizeof(test1) - 1) ? "Match" : "No Match");
    /* Possible weaknesses found:
     *  passing argument 1 of 'matches_pattern' from incompatible pointer type [-Wincompatible-pointer-types]
     *  invalid application of 'sizeof' to an incomplete type 'const char *[]'
     */
    printf("%s: %s\n", test2, matches_pattern(test2, sizeof(test2) - 1) ? "Match" : "No Match");
    /* Possible weaknesses found:
     *  passing argument 1 of 'matches_pattern' from incompatible pointer type [-Wincompatible-pointer-types]
     *  invalid application of 'sizeof' to an incomplete type 'const char *[]'
     */
    printf("%s: %s\n", test3, matches_pattern(test3, sizeof(test3) - 1) ? "Match" : "No Match");
    /* Possible weaknesses found:
     *  passing argument 1 of 'matches_pattern' from incompatible pointer type [-Wincompatible-pointer-types]
     *  invalid application of 'sizeof' to an incomplete type 'const char *[]'
     */
    printf("%s: %s\n", test4, matches_pattern(test4, sizeof(test4) - 1) ? "Match" : "No Match");

    return 0;
}