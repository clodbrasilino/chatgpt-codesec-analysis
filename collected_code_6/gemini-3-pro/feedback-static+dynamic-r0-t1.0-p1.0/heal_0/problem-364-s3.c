#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_flips(const char* str, char expected) {
    int flips = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != expected) {
            flips++;
        }
        expected = (expected == '0') ? '1' : '0';
    }
    return flips;
}

int min_flips(const char* str) {
    if (str == NULL) {
        return 0;
    }
    
    int flips_starting_with_0 = count_flips(str, '0');
    int flips_starting_with_1 = count_flips(str, '1');
    
    return min(flips_starting_with_0, flips_starting_with_1);
}

int main() {
    const char* str1 = "00110011";
    const char* str2 = "10101010";
    const char* str3 = "01010101";
    const char* str4 = "11111111";
    
    printf("%d\n", min_flips(str1));
    printf("%d\n", min_flips(str2));
    printf("%d\n", min_flips(str3));
    printf("%d\n", min_flips(str4));
    
    return 0;
}