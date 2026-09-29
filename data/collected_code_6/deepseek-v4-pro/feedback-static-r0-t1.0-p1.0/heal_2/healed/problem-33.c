#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void decimal_to_binary(int n, char *binary_str, size_t size)
{
    if (binary_str == NULL || size == 0) {
        return;
    }

    if (n == 0) {
        if (size < 2) {
            binary_str[0] = '\0';
            return;
        }
        binary_str[0] = '0';
        binary_str[1] = '\0';
        return;
    }

    int is_negative = 0;
    unsigned int num;

    if (n < 0) {
        is_negative = 1;
        num = (unsigned int)(-(n + 1)) + 1;
    } else {
        num = (unsigned int)n;
    }

    char temp[65];
    int index = 0;

    while (num > 0 && index < (int)(sizeof(temp) - 1)) {
        temp[index++] = (num & 1) ? '1' : '0';
        num >>= 1;
    }

    if (is_negative && index < (int)(sizeof(temp) - 1)) {
        if ((size_t)index + 2 > size) {
            if (size > 0) {
                binary_str[0] = '\0';
            }
            return;
        }
        temp[index++] = '-';
    } else {
        if ((size_t)index + 1 > size) {
            if (size > 0) {
                binary_str[0] = '\0';
            }
            return;
        }
    }

    int temp_index = 0;
    for (int i = index - 1; i >= 0; i--) {
        binary_str[temp_index++] = temp[i];
    }
    binary_str[temp_index] = '\0';
}

int main(void)
{
    int numbers[] = {0, 1, 2, 5, 10, 255, 1024, -1, -5, -128};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    char binary_str[65];

    for (int i = 0; i < count; i++) {
        decimal_to_binary(numbers[i], binary_str, sizeof(binary_str));
        printf("%d in binary: %s\n", numbers[i], binary_str);
    }

    return 0;
}