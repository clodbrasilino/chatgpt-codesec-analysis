#include <stdio.h>
#include <string.h>

int maxDifference(char* str) {
    int n = strlen(str);
    int max_diff = 0;
    int curr_diff = 0;
    for (int i = 0; i < n; i++) {
        curr_diff = (str[i] == '0') ? curr_diff + 1 : curr_diff - 1;
        if (curr_diff < 0)
            curr_diff = 0;
        if (curr_diff > max_diff)
            max_diff = curr_diff;
    }
    return max_diff;
}

int main() {
    char str[] = "110000100010011";
    printf("Max Difference: %d\n", maxDifference(str));
    return 0;
}