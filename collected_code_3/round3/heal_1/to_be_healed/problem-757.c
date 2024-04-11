#include <stdio.h>
#include <string.h>

int count_reverse_pairs(char* str[], int n) {
    int count = 0;
    char temp[100];
    for(int i = 0; i < n; i++) {
        strcpy(temp, str[i]);
        /* Possible weaknesses found:
         *  implicit declaration of function 'strrev'; did you mean 'strsep'? [-Wimplicit-function-declaration]
         */
        strrev(temp);
        for(int j = i+1; j < n; j++) {
            if(strcmp(temp, str[j]) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    char* str[] = {"abc", "def", "cba", "fed"};
    int n = sizeof(str)/sizeof(str[0]);
    printf("%d", count_reverse_pairs(str, n));
    return 0;
}