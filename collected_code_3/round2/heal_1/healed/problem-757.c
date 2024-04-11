#include <stdio.h>
#include <string.h>

int countReversePairs(char* list[], int n) {
    int count = 0;
    char temp[100];
    for(int i = 0; i < n; i++) {
        strcpy(temp, list[i]);
        int len = strlen(temp);
        for(int start = 0, end = len - 1; start < end; start++, end--){
            char c = temp[start]; 
            temp[start] = temp[end];
            temp[end] = c;
        }
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
    int n = sizeof(list)/sizeof(list[0]);
    printf("%d", countReversePairs(list, n));
    return 0;
}
