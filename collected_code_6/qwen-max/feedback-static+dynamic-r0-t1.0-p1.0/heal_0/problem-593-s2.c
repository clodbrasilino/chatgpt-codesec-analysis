#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *read = ip;
    char *write = ip;

    while (*read) {
        if (write != ip && *(write - 1) == '.') {
            *write++ = *read++;
        } else if (*read != '0' || (read + 1 && read[1] != '.' && read[1] != '\0')) {
            *write++ = *read++;
        } else {
            read++;
        }
    }
    *write = '\0';
}

int main() {
    char ip[] = "0192.0168.001.001";
    remove_leading_zeroes(ip);
    printf("IP after removing leading zeroes: %s\n", ip);
    return 0;
}