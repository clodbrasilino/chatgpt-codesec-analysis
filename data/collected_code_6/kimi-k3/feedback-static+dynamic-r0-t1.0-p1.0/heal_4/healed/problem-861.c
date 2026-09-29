#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 256

void sortString(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = 0;
    while (len < MAX_LENGTH && str[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        return;
    }
    
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (tolower((unsigned char)str[i]) > tolower((unsigned char)str[j])) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int areAnagrams(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = 0;
    while (len1 < MAX_LENGTH && str1[len1] != '\0') {
        len1++;
    }
    
    size_t len2 = 0;
    while (len2 < MAX_LENGTH && str2[len2] != '\0') {
        len2++;
    }
    
    if (len1 != len2) {
        return 0;
    }
    
    char *temp1 = (char *)malloc(len1 + 1);
    char *temp2 = (char *)malloc(len2 + 1);
    
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        return 0;
    }
    
    memcpy(temp1, str1, len1);
    temp1[len1] = '\0';
    
    memcpy(temp2, str2, len2);
    temp2[len2] = '\0';
    
    sortString(temp1);
    sortString(temp2);
    
    int result = (strcmp(temp1, temp2) == 0);
    
    free(temp1);
    free(temp2);
    
    return result;
}

int findAnagrams(const char *target, char list[][MAX_LENGTH], int listSize, char results[][MAX_LENGTH]) {
    if (target == NULL || list == NULL || results == NULL || listSize <= 0 || listSize > MAX_STRINGS) {
        return 0;
    }
    
    int count = 0;
    
    for (int i = 0; i < listSize && count < MAX_STRINGS; i++) {
        if (list[i] != NULL && areAnagrams(target, list[i])) {
            size_t len = 0;
            while (len < MAX_LENGTH - 1 && list[i][len] != '\0') {
                results[count][len] = list[i][len];
                len++;
            }
            results[count][len] = '\0';
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char target[MAX_LENGTH] = {0};
    char list[MAX_STRINGS][MAX_LENGTH] = {{0}};
    char results[MAX_STRINGS][MAX_LENGTH] = {{0}};
    int listSize = 0;
    int resultCount = 0;
    
    printf("Enter the target string: ");
    if (fgets(target, MAX_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    target[strcspn(target, "\n")] = '\0';
    
    printf("Enter the number of strings in the list: ");
    if (scanf("%d", &listSize) != 1 || listSize < 1 || listSize > MAX_STRINGS) {
        fprintf(stderr, "Invalid list size\n");
        return 1;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF) {
            break;
        }
    }
    
    printf("Enter %d strings:\n", listSize);
    for (int i = 0; i < listSize; i++) {
        if (fgets(list[i], MAX_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading string %d\n", i + 1);
            return 1;
        }
        list[i][strcspn(list[i], "\n")] = '\0';
    }
    
    resultCount = findAnagrams(target, list, listSize, results);
    
    if (resultCount > 0) {
        printf("Anagrams found (%d):\n", resultCount);
        for (int i = 0; i < resultCount; i++) {
            printf("%s\n", results[i]);
        }
    } else {
        printf("No anagrams found.\n");
    }
    
    return 0;
}