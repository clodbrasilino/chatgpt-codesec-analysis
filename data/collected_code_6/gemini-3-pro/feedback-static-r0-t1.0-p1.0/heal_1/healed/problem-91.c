#include <stdio.h>
#include <string.h>

int isSubstringInList(const char *substring, const char *list[], int listSize) {
    if (substring == NULL || list == NULL || listSize <= 0) {
        return 0;
    }

    for (int i = 0; i < listSize; i++) {
        if (list[i] != NULL && strstr(list[i], substring) != NULL) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *substring = "test";
    const char *list[] = {
        "hello world",
        "this is a testing string",
        "another string"
    };
    
    int listSize = (int)(sizeof(list) / sizeof(list[0])); 

    int result = isSubstringInList(substring, list, listSize);

    if (result) {
        printf("Substring found in the list.\n");
    } else {
        printf("Substring not found in the list.\n");
    }

    return 0;
}