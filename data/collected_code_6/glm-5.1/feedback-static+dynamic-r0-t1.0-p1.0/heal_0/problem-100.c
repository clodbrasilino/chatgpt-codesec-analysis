#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void increment_mid_and_propagate(int *len, char *str) {
    int mid = *len / 2;
    int left = mid - 1;
    int right = (*len % 2) ? mid + 1 : mid;
    bool left_smaller = false;

    while (left >= 0 && str[left] == str[right]) {
        left--;
        right++;
    }

    if (left < 0 || str[left] < str[right]) {
        left_smaller = true;
    }

    left = mid - 1;
    right = (*len % 2) ? mid + 1 : mid;

    while (left >= 0) {
        str[right] = str[left];
        left--;
        right++;
    }

    if (left_smaller) {
        int carry = 1;
        if (*len % 2 == 1) {
            int digit = str[mid] - '0' + carry;
            carry = digit / 10;
            str[mid] = (digit % 10) + '0';
        }
        left = mid - 1;
        right = (*len % 2) ? mid + 1 : mid;

        while (left >= 0 && carry > 0) {
            int digit = str[left] - '0' + carry;
            carry = digit / 10;
            str[left] = (digit % 10) + '0';
            str[right] = str[left];
            left--;
            right++;
        }

        if (carry > 0) {
            str[*len + 1] = '\0';
            memmove(str + 2, str + 1, *len);
            str[0] = '1';
            str[*len] = '1';
            *len = *len + 1;
        }
    }
}

void next_smallest_palindrome(char *str) {
    if (str == NULL) {
        return;
    }

    int len = strlen(str);
    if (len == 0) {
        return;
    }

    bool all_nine = true;
    for (int i = 0; i < len; i++) {
        if (str[i] != '9') {
            all_nine = false;
            break;
        }
    }

    if (all_nine) {
        str[0] = '1';
        for (int i = 1; i < len; i++) {
            str[i] = '0';
        }
        str[len] = '1';
        str[len + 1] = '\0';
        return;
    }

    increment_mid_and_propagate(&len, str);
}

int main(void) {
    char buffer1[128] = "12345";
    next_smallest_palindrome(buffer1);
    printf("%s\n", buffer1);

    char buffer2[128] = "999";
    next_smallest_palindrome(buffer2);
    printf("%s\n", buffer2);

    char buffer3[128] = "23545";
    next_smallest_palindrome(buffer3);
    printf("%s\n", buffer3);

    char buffer4[128] = "94187978322";
    next_smallest_palindrome(buffer4);
    printf("%s\n", buffer4);

    return 0;
}