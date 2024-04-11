#include <stdio.h>
#include <string.h>

void strrev(char* begin, char* end) {
    char temp;
    while (end > begin)
        temp = *begin, *begin++ = *end, *end-- = temp;
}

int count_reverse_pairs(char* str[], int n) {
    int count = 0;
    char temp[100];
    for(int i = 0; i < n; i++) {
        strcpy(temp, str[i]);
        strrev(temp, temp + strlen(temp) - 1);
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