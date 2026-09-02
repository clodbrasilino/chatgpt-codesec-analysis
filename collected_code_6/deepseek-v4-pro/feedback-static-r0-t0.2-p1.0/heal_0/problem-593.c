#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL) {
        return;
    }

    char *token;
    char *rest = ip;
    char result[16] = "";
    int first = 1;

    while ((token = strsep(&rest, ".")) != NULL) {
        if (!first) {
            strcat(result, ".");
        }
        first = 0;

        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        strcat(result, start);
    }

    strcpy(ip, result);
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";
    char ip5[] = "001.002.003.004";

    remove_leading_zeroes(ip1);
    remove_leading_zeroes(ip2);
    remove_leading_zeroes(ip3);
    remove_leading_zeroes(ip4);
    remove_leading_zeroes(ip5);

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);
    printf("%s\n", ip5);

    return 0;
}