#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps_bracket_balancing(const char *s) {
    if (s == NULL) {
        return -1;
    }
    size_t len = strnlen(s, SIZE_MAX);
    if (len == SIZE_MAX) {
        return -1;
    }
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
    size_t len = strnlen(s, SIZE_MAX);
    if (len == SIZE_MAX) {
        return -1;
    }
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

int main(int argc, char * const argv[const]) {
    (void)argc;
    if (argv[1] == NULL) {
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