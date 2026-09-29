#include <stdio.h>
#include <string.h>

int isWordLengthOdd(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    size_t length = strlen(word);
    
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