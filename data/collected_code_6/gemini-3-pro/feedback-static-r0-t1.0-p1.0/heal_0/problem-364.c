#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_flips(const char *str, char expected) {
    if (str == NULL) {
        return 0;
    }

    int flips = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != expected) {
            flips++;
        }
        expected = (expected == '0') ? '1' : '0';
    }
    return flips;
}

int min_flips(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    return min(count_flips(str, '0'), count_flips(str, '1'));
}

int main(void) {
    const char *str = "0010111";
    int flips = min_flips(str);
    printf("%d\n", flips);
    return 0;
}