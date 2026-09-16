#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_matching_positions(const char *str1, const char *str2) {
    int count = 0;
    while (*str1 && *str2) {
        if (tolower(*str1) == tolower(*str2)) {
            count++;
        }
        str1++;
        str2++;
    }
    return count;
}

int main() {
    const char *str1 = "HelloWorld";
    const char *str2 = "hElloWorld";
    int result = count_matching_positions(str1, str2);
    printf("Matching positions: %d\n", result);
    return 0;
}