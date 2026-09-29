#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_STR_COUNT 1000

struct StrFreq {
    char str[MAX_STR_LEN];
    int freq;
};

int findString(struct StrFreq sf[], int count, char* str) {
    for(int i = 0; i < count; i++) {
        if(strcmp(sf[i].str, str) == 0) {
            return i;
        }
    }
    return -1;
}

char* secondMostFrequent(char* arr[], int n) {
    struct StrFreq sf[MAX_STR_COUNT];
    int count = 0;

    for(int i = 0; i < n; i++) {
        int index = findString(sf, count, arr[i]);
        if(index != -1) {
            sf[index].freq++;
        } else {
            strcpy(sf[count].str, arr[i]);
            sf[count].freq = 1;
            count++;
        }
    }

    int first = 0, second = 0;
    for(int i = 0; i < count; i++) {
        if(sf[i].freq > sf[first].freq) {
            second = first;
            first = i;
        } else if(sf[i].freq > sf[second].freq && sf[i].freq < sf[first].freq) {
            second = i;
        }
    }

    return sf[second].str;
}

int main() {
    char* arr[] = {"apple", "banana", "apple", "orange", "banana", "banana", "lemon"};
    int n = sizeof(arr) / sizeof(arr[0]);
    char* res = secondMostFrequent(arr, n);
    if(res != NULL) {
        printf("Second most frequent string is: %s\n", res);
    } else {
        printf("No second most frequent string found.\n");
    }
    return 0;
}