#include <stdio.h>
#include <string.h>

int countOddRotations(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '1') {
            count++;
        }
    }

    return count;
}

int main() {
    const char *str1 = "101";
    int result1 = countOddRotations(str1);
    printf("%d\n", result1);

    const char *str2 = "000";
    int result2 = countOddRotations(str2);
    printf("%d\n", result2);

    const char *str3 = "1111";
    int result3 = countOddRotations(str3);
    printf("%d\n", result3);

    return 0;
}