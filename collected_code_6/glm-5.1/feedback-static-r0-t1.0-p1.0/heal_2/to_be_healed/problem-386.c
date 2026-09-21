#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_bracket_balancing(const char *s) {
    if (s == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len % 2 != 0) {
        return -1;
    }
    
    int open = 0;
    int close = 0;
    int imbalance = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '[') {
            open++;
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if (close > open) {
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                imbalance += (close - open);
            }
        } else if (s[i] == ']') {
            close++;
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if (open > 0) {
                imbalance -= (open - close + 1);
            }
        } else {
            return -1;
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    if (open != close) {
        return -1;
    }
    
    return (imbalance + 1) / 2;
}

int min_swaps_bracket_balancing_alt(const char *s) {
    if (s == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len % 2 != 0) {
        return -1;
    }
    
    int open_count = 0;
    int swaps = 0;
    char *mutable_s = strdup(s);
    
    if (mutable_s == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (mutable_s[i] == '[') {
            open_count++;
        } else if (mutable_s[i] == ']') {
            if (open_count > 0) {
                open_count--;
            } else {
                size_t j = i + 1;
                while (j < len && mutable_s[j] != '[') {
                    j++;
                }
                if (j == len) {
                    free(mutable_s);
                    return -1;
                }
                swaps += (j - i);
                char temp = mutable_s[i];
                mutable_s[i] = mutable_s[j];
                mutable_s[j] = temp;
                open_count++;
            }
        } else {
            free(mutable_s);
            return -1;
        }
    }
    
    free(mutable_s);
    return swaps;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    int result = min_swaps_bracket_balancing(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Invalid or unbalanceable bracket string\n");
        return 1;
    }
    
    printf("%d\n", result);
    return 0;
}