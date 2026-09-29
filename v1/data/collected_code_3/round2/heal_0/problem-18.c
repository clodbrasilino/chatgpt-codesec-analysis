#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

char *removeChars(char *str, char *mask_str) {
    int count[NO_OF_CHARS] = {0};
    int ip_ind = 0, res_ind = 0;
    char temp;

    while (*(mask_str + ip_ind)) {
        count[*(mask_str + ip_ind)] = 1;
        ip_ind++;
    }

    ip_ind = 0;
    while (*(str + ip_ind)) {
        temp = *(str + ip_ind);
        if (count[temp] == 0) {
            *(str + res_ind) = *(str + ip_ind);
            res_ind++;
        }
        ip_ind++;
    }

    *(str + res_ind) = '\0';

    return str;
}

int main() {
    char str[] = "Hello, World!";
    char mask_str[] = "lo";
    printf("%s", removeChars(str, mask_str));
    return 0;
}