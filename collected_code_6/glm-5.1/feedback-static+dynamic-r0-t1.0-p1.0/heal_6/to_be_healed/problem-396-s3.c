#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_same_start_end(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char escaped_char[5] = {0};

    if (strchr(".^$*+?\\[({", str[0]) != NULL) {
        escaped_char[0] = '\\';
        escaped_char[1] = str[0];
    } else {
        escaped_char[0] = str[0];
    }

    size_t escaped_len = strnlen(escaped_char, sizeof(escaped_char));
    size_t full_pattern_len = 1 + escaped_len + 2 + escaped_len + 1 + 1;

    char *full_pattern = malloc(full_pattern_len);
    if (full_pattern == NULL) {
        return 0;
    }

    snprintf(full_pattern, full_pattern_len, "^%s.*%s$", escaped_char, escaped_char);

    /* Possible weaknesses found:
     *  'REG_NOSUB' undeclared (first use in this function)
     *  use of undeclared identifier 'regex'
     *  'REG_EXTENDED' undeclared (first use in this function)
     *  use of undeclared identifier 'REG_EXTENDED'
     *  implicit declaration of function 'regcomp' [-Wimplicit-function-declaration]
     *  'regex' undeclared (first use in this function)
     *  use of undeclared identifier 'REG_NOSUB'
     *  call to undeclared function 'regcomp'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  each undeclared identifier is reported only once for each function it appears in
     */
    int ret = regcomp(&regex, full_pattern, REG_EXTENDED | REG_NOSUB);
    free(full_pattern);

    if (ret != 0) {
        return 0;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  implicit declaration of function 'regexec' [-Wimplicit-function-declaration]
     *  call to undeclared function 'regexec'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    ret = regexec(&regex, str, 0, NULL, 0);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  implicit declaration of function 'regfree'; did you mean 'free'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'regfree'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    regfree(&regex);

    return ret == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (check_same_start_end(argv[1])) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }

    return EXIT_SUCCESS;
}