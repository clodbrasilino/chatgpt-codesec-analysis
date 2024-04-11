#include <stdio.h>
#include <string.h>

int count_reverse_pairs(char* list[], int n) {
    int count = 0;
    char temp[100];
    for(int i = 0; i < n; i++) {
        strcpy(temp, list[i]);
        /* Possible weaknesses found:
         *  implicit declaration of function 'strrev'; did you mean 'strsep'? [-Wimplicit-function-declaration]
         */
        strrev(temp);
        for(int j = i + 1; j < n; j++) {
            if(strcmp(temp, list[j]) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    char* list[] = {"abc", "def", "cba", "fed"};
    int n = sizeof(list) / sizeof(list[0]);
    printf("%d", count_reverse_pairs(list, n));
    return 0;
}