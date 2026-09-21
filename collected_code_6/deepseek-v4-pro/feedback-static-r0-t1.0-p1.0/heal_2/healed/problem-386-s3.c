#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsForBalance(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 1024);
    if (len == 0) {
        return 0;
    }

    char *buf = malloc(len + 1);
    if (buf == NULL) {
        return 0;
    }

    memcpy(buf, str, len);
    buf[len] = '\0';

    int balance = 0;
    int swaps = 0;
    size_t start = 0;
    size_t end = len - 1;

    while (start < end) {
        if (buf[start] == '[') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            while (start < end && buf[end] != '[') {
                end--;
            }
            if (start < end) {
                char temp = buf[start];
                buf[start] = buf[end];
                buf[end] = temp;
                swaps++;
                balance = 1;
                end--;
            }
        }
        start++;
    }

    free(buf);
    return swaps;
}

int main(void) {
    char test1[] = "]][[";
    char test2[] = "[]][][";
    char test3[] = "[[][]]";
    char test4[] = "][";

    printf("Minimum swaps for \"%s\": %d\n", test1, minSwapsForBalance(test1));
    printf("Minimum swaps for \"%s\": %d\n", test2, minSwapsForBalance(test2));
    printf("Minimum swaps for \"%s\": %d\n", test3, minSwapsForBalance(test3));
    printf("Minimum swaps for \"%s\": %d\n", test4, minSwapsForBalance(test4));

    return 0;
}