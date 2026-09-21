#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 256
#define INT_BUFFER_SIZE 64

void sortString(char *str, size_t len) {
    if (str == NULL || len == 0) {
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

size_t safeStrlen(const char *str, size_t maxlen) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

int areAnagrams(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = safeStrlen(str1, MAX_LENGTH);
    size_t len2 = safeStrlen(str2, MAX_LENGTH);
    
    if (len1 != len2 || len1 >= MAX_LENGTH || len2 >= MAX_LENGTH) {
        return 0;
    }
    
    char *temp1 = (char *)malloc(len1 + 1);
    char *temp2 = (char *)malloc(len2 + 1);
    
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        return 0;
    }
    
    strncpy(temp1, str1, len1);
    temp1[len1] = '\0';
    strncpy(temp2, str2, len2);
    temp2[len2] = '\0';
    
    sortString(temp1, len1);
    sortString(temp2, len2);
    
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
            size_t copyLen = safeStrlen(list[i], MAX_LENGTH - 1);
            if (copyLen < MAX_LENGTH) {
                strncpy(results[count], list[i], copyLen);
                results[count][copyLen] = '\0';
                count++;
            }
        }
    }
    
    return count;
}

int clearInputBuffer(void) {
    int c;
    int count = 0;
    
    while ((c = getchar()) != '\n' && c != EOF) {
        count++;
        if (count > 10000) {
            return 0;
        }
    }
    
    if (c == EOF && count == 0) {
        return 0;
    }
    
    return 1;
}

int readLine(char *buffer, size_t size) {
    if (buffer == NULL || size == 0 || size > MAX_LENGTH) {
        return 0;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    
    size_t len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        if (!clearInputBuffer()) {
            return 0;
        }
    }
    
    return 1;
}

int readInt(int *value, int min, int max) {
    char buffer[INT_BUFFER_SIZE];
    char *endptr;
    long temp;
    
    if (value == NULL || min > max) {
        return 0;
    }
    
    memset(buffer, 0, sizeof(buffer));
    
    if (!readLine(buffer, sizeof(buffer))) {
        return 0;
    }
    
    errno = 0;
    temp = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || temp < min || temp > max) {
        return 0;
    }
    
    *value = (int)temp;
    return 1;
}

int main(void) {
    char *target = NULL;
    char (*list)[MAX_LENGTH] = NULL;
    char (*results)[MAX_LENGTH] = NULL;
    int listSize = 0;
    int resultCount = 0;
    int i;
    
    target = (char *)calloc(MAX_LENGTH, sizeof(char));
    if (target == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the target string: ");
    if (!readLine(target, MAX_LENGTH)) {
        fprintf(stderr, "Error reading input\n");
        free(target);
        return 1;
    }
    
    printf("Enter the number of strings in the list: ");
    if (!readInt(&listSize, 1, MAX_STRINGS)) {
        fprintf(stderr, "Invalid list size\n");
        free(target);
        return 1;
    }
    
    list = (char (*)[MAX_LENGTH])calloc(MAX_STRINGS, sizeof(char[MAX_LENGTH]));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(target);
        return 1;
    }
    
    results = (char (*)[MAX_LENGTH])calloc(MAX_STRINGS, sizeof(char[MAX_LENGTH]));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(target);
        free(list);
        return 1;
    }
    
    printf("Enter %d strings:\n", listSize);
    for (i = 0; i < listSize; i++) {
        if (!readLine(list[i], MAX_LENGTH)) {
            fprintf(stderr, "Error reading string %d\n", i + 1);
            free(target);
            free(list);
            free(results);
            return 1;
        }
    }
    
    resultCount = findAnagrams(target, list, listSize, results);
    
    if (resultCount > 0) {
        printf("Anagrams found (%d):\n", resultCount);
        for (i = 0; i < resultCount; i++) {
            printf("%s\n", results[i]);
        }
    } else {
        printf("No anagrams found.\n");
    }
    
    free(target);
    free(list);
    free(results);
    
    return 0;
}