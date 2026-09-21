#include <stdio.h>
#include <string.h>

int min_swaps_for_balance(char *str) {
    int balance = 0;
    int swaps = 0;
    int left = 0;
    size_t len = strnlen(str, 1024);
    int right = (len > 0) ? (int)(len - 1) : 0;

    if (len == 0) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            balance++;
        } else if (str[i] == ']') {
            balance--;
        }

        if (balance < 0) {
            while (left < right && str[left] != ']') {
                left++;
            }
            while (right > left && str[right] != '[') {
                right--;
            }

            if (left < right) {
                char temp = str[left];
                str[left] = str[right];
                str[right] = temp;
                swaps++;
                balance = 1;
                left++;
                right--;
            }
        }
    }

    return swaps;
}

int main(void) {
    char str1[] = "[]][][";
    char str2[] = "[[][]]";
    char str3[] = "]][[";

    printf("String: %s, Min swaps: %d\n", str1, min_swaps_for_balance(str1));
    printf("String: %s, Min swaps: %d\n", str2, min_swaps_for_balance(str2));
    printf("String: %s, Min swaps: %d\n", str3, min_swaps_for_balance(str3));

    return 0;
}