#include <stdio.h>
#include <string.h>

int findMaxDiff(const char *binary) {
    int max_diff = 0, current_diff = 0;
    for (const char *p = binary; *p; ++p) {
        if (*p == '0') {
            current_diff++;
        } else {
            current_diff--;
        }
        if (current_diff < 0) {
            current_diff = 0;
        }
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }
    return max_diff;
}

int main() {
    const char *binary = "10010110";
    int max_diff = findMaxDiff(binary);
    printf("Maximum difference: %d\n", max_diff);
    return 0;
}