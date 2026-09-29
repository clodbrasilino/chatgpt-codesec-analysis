#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_bracket_balancing(const char *s) {
    if (s == NULL) {
        return -1;
    }
    size_t len = strnlen(s, SIZE_MAX);
    if (len % 2 != 0) {
        return -1;
    }
    
    int bracket_open = 0;
    int bracket_close = 0;
    int imbalance = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '[') {
            bracket_open++;
            if (bracket_close > bracket_open) {
                imbalance += (bracket_close - bracket_open);
            }
        } else if (s[i] == ']') {
            bracket_close++;
            if (bracket_open > 0) {
                imbalance -= (bracket_open - bracket_close + 1);
            }
        } else {
            return -1;
        }
    }
    
    if (bracket_open != bracket_close) {
        return -1;
    }
    
    return (imbalance + 1) / 2;
}

int min_swaps_bracket_balancing_alt(const char *s) {
    if (s == NULL) {
        return -1;
    }
    size_t len = strnlen(s, SIZE_MAX);
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