#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void increment_mid(char *num, int len) {
    int mid = len / 2;
    int i = mid - 1;
    bool carry = false;

    if (len % 2 != 0) {
        num[mid]++;
        if (num[mid] > '9') {
            num[mid] = '0';
            carry = true;
        } else {
            return;
        }
    } else {
        carry = true;
    }

    for (i = (len % 2 != 0 ? mid - 1 : mid - 1); i >= 0 && carry; i--) {
        num[i]++;
        if (num[i] > '9') {
            num[i] = '0';
            carry = true;
        } else {
            carry = false;
        }
    }

    if (carry) {
        num[0] = '1';
        num[len] = '0';
        num[len + 1] = '\0';
    }
}

bool is_greater(char *num, int len) {
    int start = 0;
    int end = len - 1;

    while (start < end) {
        if (num[start] < num[end]) {
            return false;
        } else if (num[start] > num[end]) {
            return true;
        }
        start++;
        end--;
    }
    return false;
}

void mirror(char *num, int len) {
    int start = 0;
    int end = len - 1;

    while (start < end) {
        num[end] = num[start];
        start++;
        end--;
    }
}

char* next_smallest_palindrome(char *num) {
    if (num == NULL) {
        return NULL;
    }

    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        if (num[i] < '0' || num[i] > '9') {
            return NULL;
        }
    }

    bool all_nine = true;
    for (int i = 0; i < len; i++) {
        if (num[i] != '9') {
            all_nine = false;
            break;
        }
    }

    if (all_nine) {
        char *res = (char *)malloc(len + 3);
        if (res == NULL) {
            return NULL;
        }
        res[0] = '1';
        for (int i = 1; i < len; i++) {
            res[i] = '0';
        }
        res[len] = '1';
        res[len + 1] = '\0';
        return res;
    }

    char *temp = (char *)malloc(len + 2);
    if (temp == NULL) {
        return NULL;
    }
    strcpy(temp, num);

    if (!is_greater(temp, len)) {
        increment_mid(temp, len);
    }

    int current_len = strlen(temp);
    mirror(temp, current_len);

    return temp;
}

int main() {
    char num1[] = "23545";
    char *res1 = next_smallest_palindrome(num1);
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char num2[] = "12321";
    char *res2 = next_smallest_palindrome(num2);
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    char num3[] = "999";
    char *res3 = next_smallest_palindrome(num3);
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    char num4[] = "9";
    char *res4 = next_smallest_palindrome(num4);
    if (res4 != NULL) {
        printf("%s\n", res4);
        free(res4);
    }

    return 0;
}