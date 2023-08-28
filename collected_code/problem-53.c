#include <stdio.h>
#include <stdbool.h>

bool is_first_last_equal(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    if (len <= 1) {
        return true;
    }
    return (str[0] == str[len - 1]);
}