#include <stdio.h>
#include <string.h>

void strrev(char* begin, char *end)
{
    char temp;
    while (begin < end) 
    {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

int count_reverse_pairs(char* list[], int n) {
    int count = 0;
    char temp[100];
    for(int i = 0; i < n; i++) {
        strcpy(temp, list[i]);
        strrev(temp, temp + strlen(temp) - 1);
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