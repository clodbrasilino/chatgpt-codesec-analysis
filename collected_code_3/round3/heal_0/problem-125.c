#include <stdio.h>
#include <string.h>

int maxDifference(char* str) {
    int n = strlen(str);
    int current_diff = 0;
    int max_diff = 0;
    int i;

    for (i = 0; i < n; i++) {
        current_diff = (str[i] == '0') ? current_diff + 1 : current_diff - 1;

        if (current_diff < 0)
            current_diff = 0;

        if (current_diff > max_diff)
            max_diff = current_diff;
    }

    return max_diff;
}

int main() {
    char str[] = "110000100010111";
    printf("Maximum difference is %d\n", maxDifference(str));
    return 0;
}