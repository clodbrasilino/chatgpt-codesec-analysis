#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int countFlips(const char *str, char expected) {
    int flips = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != expected) {
            flips++;
        }
        expected = (expected == '0') ? '1' : '0';
    }
    return flips;
}

int minFlipsAlternating(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int flipsStartingWith0 = countFlips(str, '0');
    int flipsStartingWith1 = countFlips(str, '1');
    
    return min(flipsStartingWith0, flipsStartingWith1);
}

int main(void) {
    const char *binaryString = "00101011";
    
    int result = minFlipsAlternating(binaryString);
    printf("%d\n", result);
    
    return 0;
}