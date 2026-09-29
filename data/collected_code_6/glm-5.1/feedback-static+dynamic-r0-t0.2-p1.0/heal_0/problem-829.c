#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int count;
} Entry;

char* findSecondMostRepeated(char **strings, int size) {
    if (size < 2) {
        return NULL;
    }

    int capacity = 16;
    Entry *entries = malloc(capacity * sizeof(Entry));
    if (!entries) {
        return NULL;
    }
    int uniqueCount = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(entries[j].key, strings[i]) == 0) {
                entries[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (uniqueCount == capacity) {
                capacity *= 2;
                Entry *temp = realloc(entries, capacity * sizeof(Entry));
                if (!temp) {
                    for (int k = 0; k < uniqueCount; k++) {
                        free(entries[k].key);
                    }
                    free(entries);
                    return NULL;
                }
                entries = temp;
            }
            entries[uniqueCount].key = malloc(strlen(strings[i]) + 1);
            if (!entries[uniqueCount].key) {
                for (int k = 0; k < uniqueCount; k++) {
                    free(entries[k].key);
                }
                free(entries);
                return NULL;
            }
            strcpy(entries[uniqueCount].key, strings[i]);
            entries[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    if (uniqueCount < 2) {
        for (int i = 0; i < uniqueCount; i++) {
            free(entries[i].key);
        }
        free(entries);
        return NULL;
    }

    int first = -1;
    int second = -1;

    for (int i = 0; i < uniqueCount; i++) {
        if (first == -1 || entries[i].count > entries[first].count) {
            second = first;
            first = i;
        } else if (second == -1 || entries[i].count > entries[second].count) {
            if (entries[i].count != entries[first].count) {
                second = i;
            }
        }
    }

    char *result = NULL;
    if (second != -1) {
        result = entries[second].key;
        entries[second].key = NULL;
    }

    for (int i = 0; i < uniqueCount; i++) {
        free(entries[i].key);
    }
    free(entries);

    return result;
}

int main() {
    char *arr[] = {"apple", "banana", "apple", "orange", "banana", "apple", "banana"};
    int size = sizeof(arr) / sizeof(arr[0]);

    char *result = findSecondMostRepeated(arr, size);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("No second most repeated string found.\n");
    }

    return 0;
}