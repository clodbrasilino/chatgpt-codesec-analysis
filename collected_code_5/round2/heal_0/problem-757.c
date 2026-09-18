#include<stdio.h>
#include<string.h>

char* reverseString(char* string) {
    int len = strlen(string);
    char* reverse = (char*)malloc(sizeof(char)*(len+1));

    for(int i = 0; i<len; i++) {
        reverse[i] = string[len-1-i];
    }
    reverse[len] = '\0';
    
    return reverse;
}

int countReversePairs(char** list, int count) {
    int reversePairCount = 0;
    for(int i = 0; i < count; i++) {
        for(int j = i+1; j < count; j++) {
            char* reverse = reverseString(list[i]);
            if(strcmp(reverse, list[j]) == 0) {
                reversePairCount++;
            }
            free(reverse);
        }
    }
    return reversePairCount;
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);
    
    char** list = (char**)malloc(sizeof(char*)*n);
    for(int i = 0; i < n; ++i) {
        list[i] = (char*)malloc(sizeof(char)*100);
    }

    printf("Enter the strings: \n");
    for(int i = 0; i < n; ++i) {
        scanf("%s", list[i]);
    }

    int result = countReversePairs(list, n);
    printf("Number of reverse pairs: %d\n", result);
    
    for(int i = 0; i < n; ++i) {
        free(list[i]);
    }
    free(list);

    return 0;
    
}