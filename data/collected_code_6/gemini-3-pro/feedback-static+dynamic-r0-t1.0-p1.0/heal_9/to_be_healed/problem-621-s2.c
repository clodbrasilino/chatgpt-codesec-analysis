#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_numeric(const char* s) {
    if (!s || !*s) return 0;
    if (*s == '-' && s[1]) s++;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_line[4096] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char k_line[1024] = {0};
    
    if (!fgets(input_line, sizeof(input_line), stdin)) {
        return 0;
    }
    input_line[strcspn(input_line, "\r\n")] = '\0';
    
    int k = 0;
    if (fgets(k_line, sizeof(k_line), stdin)) {
        k_line[strcspn(k_line, "\r\n")] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(k_line) > 0) {
            /* Possible weaknesses found:
             * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
             */
            k = atoi(k_line);
        } else {
            char *last_space = strrchr(input_line, ' ');
            if (last_space) {
                /* Possible weaknesses found:
                 * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
                 */
                k = atoi(last_space + 1);
                *last_space = '\0';
            }
        }
    } else {
        char *last_space = strrchr(input_line, ' ');
        if (last_space) {
            /* Possible weaknesses found:
             * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
             */
            k = atoi(last_space + 1);
            *last_space = '\0';
        }
    }

    printf("[");
    int first = 1;
    char* token = strtok(input_line, " ");
    while (token) {
        if (!first) printf(", ");
        if (is_numeric(token)) {
            long long val = strtoll(token, NULL, 10);
            printf("'%lld'", val + k);
        } else {
            printf("'%s'", token);
        }
        first = 0;
        token = strtok(NULL, " ");
    }
    printf("]\n");
    
    return 0;
}