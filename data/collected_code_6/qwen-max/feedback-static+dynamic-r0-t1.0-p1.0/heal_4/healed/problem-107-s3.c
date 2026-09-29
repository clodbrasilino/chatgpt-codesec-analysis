#include <stdio.h>
#include <inttypes.h>
#include <string.h>

int count_hex_numbers(int from, int to) {
    if (from > to) return 0;
    int count = 0;
    for (int i = from; i <= to; i++) {
        char buf[9] = {0};
        snprintf(buf, sizeof(buf), "%x", i);
        size_t len = strnlen(buf, sizeof(buf));
        if (len == strspn(buf, "0123456789abcdef")) count++;
    }
    return count;
}

int main() {
    int from, to;
    printf("Enter the range (from to): ");
    if (scanf("%d %d", &from, &to) == 2) {
        int result = count_hex_numbers(from, to);
        printf("Count: %d\n", result);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}