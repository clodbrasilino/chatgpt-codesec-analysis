#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int minSwaps(const char* s1, const char* s2) {
    size_t n1 = 0;
    while (s1[n1] && (s1[n1] == '0' || s1[n1] == '1')) n1++;
    size_t n2 = 0;
    while (s2[n2] && (s2[n2] == '0' || s2[n2] == '1')) n2++;

    if (n1 != n2 || s1[n1] != '\0' || s2[n2] != '\0') {
        return -1;
    }

    int count[2] = {0, 0};
    for (size_t i = 0; i < n1; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }

    if (count[0] == count[1]) {
        return count[0];
    } else {
        return -1;
    }
}

int main() {
    const char *test_cases[][2] = {
        {"101", "010"},
        {"110", "001"},
        {"1100", "0011"}
    };

    for (size_t i = 0; i < 3; i++) {
        int swaps = minSwaps(test_cases[i][0], test_cases[i][1]);
        if (swaps != -1) {
            printf("Minimum number of swaps: %d\n", swaps);
        } else {
            printf("Not Possible\n");
        }
    }

    return 0;
}