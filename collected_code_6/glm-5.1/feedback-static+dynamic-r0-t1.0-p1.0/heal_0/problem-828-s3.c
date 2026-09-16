#include <stdio.h>
#include <ctype.h>

typedef struct {
    int alphabets;
    int digits;
    int special;
} CharCount;

CharCount count_chars(const char *str) {
    CharCount counts = {0, 0, 0};
    if (str == NULL) {
        return counts;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            counts.alphabets++;
        } else if (isdigit((unsigned char)str[i])) {
            counts.digits++;
        } else {
            counts.special++;
        }
    }
    
    return counts;
}

int main(int argc, char *argv[]) {
    const char *text = "Hello, World! 123 #";
    CharCount result = count_chars(text);
    
    printf("Alphabets: %d\n", result.alphabets);
    printf("Digits: %d\n", result.digits);
    printf("Special: %d\n", result.special);
    
    return 0;
}