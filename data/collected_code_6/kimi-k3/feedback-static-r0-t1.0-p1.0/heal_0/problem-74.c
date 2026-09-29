#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool follows_pattern(const int *data, size_t data_len, const int *pattern, size_t pattern_len) {
    if (data == NULL || pattern == NULL) {
        return false;
    }
    
    if (pattern_len == 0) {
        return false;
    }
    
    if (data_len < pattern_len) {
        return false;
    }
    
    size_t data_idx = 0;
    size_t pattern_idx = 0;
    
    while (data_idx < data_len && pattern_idx < pattern_len) {
        if (data[data_idx] == pattern[pattern_idx]) {
            pattern_idx++;
        }
        data_idx++;
    }
    
    return pattern_idx == pattern_len;
}

int main(void) {
    int data[] = {1, 5, 2, 8, 3, 9, 4};
    int pattern[] = {1, 2, 3, 4};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t pattern_len = sizeof(pattern) / sizeof(pattern[0]);
    
    if (follows_pattern(data, data_len, pattern, pattern_len)) {
        printf("Sequence follows the pattern\n");
    } else {
        printf("Sequence does not follow the pattern\n");
    }
    
    int data2[] = {1, 2, 4, 3};
    int pattern2[] = {1, 2, 3};
    size_t data2_len = sizeof(data2) / sizeof(data2[0]);
    size_t pattern2_len = sizeof(pattern2) / sizeof(pattern2[0]);
    
    if (follows_pattern(data2, data2_len, pattern2, pattern2_len)) {
        printf("Sequence 2 follows the pattern\n");
    } else {
        printf("Sequence 2 does not follow the pattern\n");
    }
    
    return 0;
}