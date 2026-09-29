#include <stdio.h>
#include <string.h>

void removeChars(char *str1, char *str2) {
    int hash[256] = {0};
    int ip_ind = 0, res_ind = 0;
    char temp;

    while(*(str2 + ip_ind)) {
        hash[*(str2 + ip_ind)] = 1;
        ip_ind++;
    }

    ip_ind = 0;
    while(*(str1 + ip_ind)) {
        temp = *(str1 + ip_ind);
        if(hash[temp] == 0) {
            *(str1 + res_ind) = *(str1 + ip_ind);
            res_ind++;
        }
        ip_ind++;
    }

    *(str1 + res_ind) = '\0';
}

int main() {
    char str1[100] = "Hello, World!";
    char str2[100] = "World";
    removeChars(str1, str2);
    printf("%s\n", str1);
    return 0;
}