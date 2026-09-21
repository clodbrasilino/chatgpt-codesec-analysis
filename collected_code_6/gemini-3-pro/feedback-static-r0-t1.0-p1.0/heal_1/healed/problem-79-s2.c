#include <stdio.h>
#include <stddef.h>

#define MAX_STR_LEN 4096

int isWordLengthOdd(const char *word) {
    size_t length = 0;
    
    if (word == NULL) {
        return 0;
    }
    
    while (length < MAX_STR_LEN && word[length] != '\0') {
        length++;
    }
    
    if (length % 2 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *testWord1 = "hello";
    const char *testWord2 = "world!";
    const char *testWord3 = NULL;
    
    int result1 = isWordLengthOdd(testWord1);
    int result2 = isWordLengthOdd(testWord2);
    int result3 = isWordLengthOdd(testWord3);
    
    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
    
    return 0;
}