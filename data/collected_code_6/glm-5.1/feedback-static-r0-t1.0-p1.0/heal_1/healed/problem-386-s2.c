#include <stdio.h>
#include <stdlib.h>

int min_swaps(const char *str, size_t len) {
    if (len == 0) return 0;
    int *positions = (int *)malloc(len * sizeof(int));
    if (!positions) return -1;
    int pos_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            positions[pos_count++] = i;
        }
    }
    int swaps = 0;
    int balance = 0;
    int next_open = 0;
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
            int target_pos = positions[next_open];
            swaps += target_pos - i;
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
    printf("%d\n", min_swaps(str1, sizeof(str1) - 1));
    char str2[] = "[[][]]";
    printf("%d\n", min_swaps(str2, sizeof(str2) - 1));
    char str3[] = "]]][[[";
    printf("%d\n", min_swaps(str3, sizeof(str3) - 1));
    char str4[] = "][";
    printf("%d\n", min_swaps(str4, sizeof(str4) - 1));
    return 0;
}