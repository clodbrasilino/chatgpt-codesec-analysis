#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 102

int countUpperCaseChars(const char *str, size_t length) {
    int count = 0;
    if (str == NULL) return count;

    for (size_t i = 0; i < length; ++i) {
        if (isupper((unsigned char)str[i])) count++;
    }

    return count;
}

int main() {
    char str[MAX_SIZE];

    printf("Enter a string: ");
    
    if(fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';
        size_t length = strnlen(str, MAX_SIZE);

        if (length >= MAX_SIZE) {
	    printf("Size limit exceeded\n");
	    return 1;
	}

        int result = countUpperCaseChars(str, length);
        printf("Number of upper case characters: %d\n", result);
    }

    return 0;
}