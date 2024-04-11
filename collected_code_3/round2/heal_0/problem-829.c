#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_STR_COUNT 1000

typedef struct {
    char str[MAX_STR_LEN];
    int count;
} WordCount;

int find_index(WordCount wc[], int n, char* str) {
    for(int i = 0; i < n; i++) {
        if(strcmp(wc[i].str, str) == 0) {
            return i;
        }
    }
    return -1;
}

char* second_most_repeated(char* str[], int n) {
    WordCount wc[MAX_STR_COUNT];
    int distinct_word_count = 0;

    for(int i = 0; i < n; i++) {
        int index = find_index(wc, distinct_word_count, str[i]);
        if(index == -1) {
            strcpy(wc[distinct_word_count].str, str[i]);
            wc[distinct_word_count].count = 1;
            distinct_word_count++;
        } else {
            wc[index].count++;
        }
    }

    int first_max = 0, second_max = 0;
    for(int i = 0; i < distinct_word_count; i++) {
        if(wc[i].count > wc[first_max].count) {
            second_max = first_max;
            first_max = i;
        } else if(wc[i].count > wc[second_max].count && wc[i].count < wc[first_max].count) {
            second_max = i;
        }
    }

    return wc[second_max].str;
}

int main() {
    char* str[] = {"test", "hello", "world", "hello", "test", "test", "hello", "test"};
    int n = sizeof(str) / sizeof(str[0]);
    char* res = second_most_repeated(str, n);
    printf("%s\n", res);
    return 0;
}