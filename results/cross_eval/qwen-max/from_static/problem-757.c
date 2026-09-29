#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_reverse_pairs(char *strings[], int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            size_t len_i = strnlen(strings[i], 100);
            size_t len_j = strnlen(strings[j], 100);
            if (len_i == len_j) {
                int is_reverse = 1;
                for (size_t k = 0; k < len_i; ++k) {
                    if (strings[i][k] != strings[j][len_i - 1 - k]) {
                        is_reverse = 0;
                        break;
                    }
                }
                if (is_reverse) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    char *list[] = {"abc", "cba", "bca", "d"};
    int n = sizeof(list) / sizeof(list[0]);
    int result = count_reverse_pairs(list, n);
    printf("Number of reverse string pairs: %d\n", result);
    return 0;
}