#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_regex(const char *pattern, const char *string) {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex_t'
     *  unknown type name 'regex_t'
     */
    regex_t regex;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  'REG_EXTENDED' undeclared (first use in this function)
     *  use of undeclared identifier 'REG_EXTENDED'
     *  implicit declaration of function 'regcomp' [-Wimplicit-function-declaration]
     *  call to undeclared function 'regcomp'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  each undeclared identifier is reported only once for each function it appears in
     */
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  implicit declaration of function 'regexec' [-Wimplicit-function-declaration]
     *  call to undeclared function 'regexec'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    ret = regexec(&regex, string, 0, NULL, 0);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  implicit declaration of function 'regfree'; did you mean 'free'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'regfree'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    regfree(&regex);
    if (ret == 0) {
        return 1;
    }
    return 0;
}

void categorize_string(const char *str, size_t len, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (isupper((unsigned char)c)) {
            (*upper)++;
        } else if (islower((unsigned char)c)) {
            (*lower)++;
        } else if (isdigit((unsigned char)c)) {
            (*digit)++;
        } else if (!isalnum((unsigned char)c) && isprint((unsigned char)c)) {
            (*special)++;
        }
    }
}

int main(void) {
    const char *input = "Hello World! 123 @#$";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    int upper, lower, digit, special;
    categorize_string(input, len, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    return 0;
}