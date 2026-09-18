#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int check_even_odd (uint32_t number) {
    return (number & 1) ? -1 : 0;
}

int main() {
    char hex_num[10];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hex_num);
    uint32_t val = (uint32_t)strtol(hex_num, NULL, 16);
    if (check_even_odd(val) == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return 0;
}