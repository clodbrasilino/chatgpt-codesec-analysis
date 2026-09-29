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
    
    int open_brace = 0;
    int close_brace = 0;
    int swaps = 0;
    int imbalance = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '[') {
            open_brace++;
            if (close_brace > open_brace) {
                imbalance += (close_brace - open_brace);
            }
        } else if (s[i] == ']') {
            close_brace++;
            if (open_brace > 0) {
                imbalance -= (open_brace - close_brace + 1);
            }
        } else {
            return -1;
        }
    }
    
    if (open_brace != close_brace) {
        return -1;
    }
    
    swaps = (imbalance + 1) / 2;
    return swaps;
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
    
    char *mutable_s = strdup(s);
    if (mutable_s == NULL) {
        return -1;
    }
    
    int open_count = 0;
    int swaps = 0;
    
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