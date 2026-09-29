#include <stdio.h>
#include <stdlib.h>

int count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        int sum = 0;
        for (int j = i; str[j] != '\0'; j++) {
            if (str[j] < '0' || str[j] > '9') {
                return 0; 
            }
            sum += (str[j] - '0');
            if (sum == (j - i + 1)) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *test_str = "12034";
    int result = count_substrings(test_str);
    printf("%d\n", result);
    return 0;
}