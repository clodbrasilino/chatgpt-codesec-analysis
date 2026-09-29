#include <stdbool.h>
#include <stddef.h>

bool follows_pattern(const int *sequence, size_t seq_len, const int *pattern, size_t pat_len) {
    if (sequence == NULL || pattern == NULL) {
        return false;
    }
    if (pat_len == 0) {
        return seq_len == 0;
    }
    if (seq_len < pat_len) {
        return false;
    }
    
    for (size_t i = 0; i < pat_len; i++) {
        if (sequence[i] != pattern[i]) {
            return false;
        }
    }
    
    size_t j = 0;
    for (size_t i = pat_len; i < seq_len; i++) {
        if (j < pat_len && sequence[i] == pattern[j]) {
            j++;
        } else if (j > 0 && sequence[i] == pattern[j - 1]) {
            continue;
        } else {
            j = 0;
            if (sequence[i] == pattern[0]) {
                j = 1;
            }
        }
        
        if (j == pat_len) {
            return true;
        }
    }
    
    return j == pat_len;
}

int main(void) {
    const int seq1[] = {1, 2, 3, 1, 2, 3};
    const int pat1[] = {1, 2, 3};
    
    bool result1 = follows_pattern(seq1, 6, pat1, 3);
    
    const int seq2[] = {5, 6, 7, 8};
    const int pat2[] = {5, 6, 7};
    
    bool result2 = follows_pattern(seq2, 4, pat2, 3);
    
    const int seq3[] = {1, 2, 3};
    const int pat3[] = {1, 2, 3};
    
    bool result3 = follows_pattern(seq3, 3, pat3, 3);
    
    (void)result1;
    (void)result2;
    (void)result3;
    
    return 0;
}