#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_reverse_pairs(char *strings[], int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int len_i = strlen(strings[i]);
            int len_j = strlen(strings[j]);
            if (len_i == len_j) {
                int is_reverse = 1;
                for (int k = 0; k < len_i; ++k) {
                    if (strings[i][k] != strings[j][len_i - k - 1]) {
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
    char *strings[] = {"abc", "cba", "bca", "xyz", "zyx", "def"};
    int size = sizeof(strings) / sizeof(strings[0]);
    int result = count_reverse_pairs(strings, size);
    printf("Number of reverse string pairs: %d\n", result);
    return 0;
}