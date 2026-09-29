#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int min_swaps(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == 0) return 0;
    size_t pos_count = 0;
    size_t alloc_size = len * sizeof(size_t);
    if (alloc_size / sizeof(size_t) != len) return -1;
    size_t *positions = (size_t *)malloc(alloc_size);
    if (!positions) return -1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            positions[pos_count++] = i;
        }
    }
    int swaps = 0;
    int balance = 0;
    size_t next_open = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            balance++;
            next_open++;
        } else {
            balance--;
        }
        if (balance < 0) {
            if (next_open >= pos_count) {
                free(positions);
                return -1;
            }
            swaps += (int)(positions[next_open] - i);
            balance = 1;
            next_open++;
        }
    }
    free(positions);
    if (balance != 0) return -1;
    return swaps;
}

int main() {
    char str1[] = "[]][][";
    printf("%d\n", min_swaps(str1, sizeof(str1)));
    char str2[] = "[[][]]";
    printf("%d\n", min_swaps(str2, sizeof(str2)));
    char str3[] = "]]][[[";
    printf("%d\n", min_swaps(str3, sizeof(str3)));
    char str4[] = "][";
    printf("%d\n", min_swaps(str4, sizeof(str4)));
    return 0;
}