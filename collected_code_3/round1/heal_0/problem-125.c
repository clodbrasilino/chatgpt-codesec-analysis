#include <stdio.h>
#include <string.h>

int maxDifference(char* str) {
    int max_diff = 0;
    int diff = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        diff = (str[i] == '0') ? diff + 1 : diff - 1;
        if (diff < 0)
            diff = 0;
        if (diff > max_diff)
            max_diff = diff;
    }
    return max_diff;
}

int main() {
    char str[] = "110000100010111";
    printf("Maximum difference is %d\n", maxDifference(str));
    return 0;
}