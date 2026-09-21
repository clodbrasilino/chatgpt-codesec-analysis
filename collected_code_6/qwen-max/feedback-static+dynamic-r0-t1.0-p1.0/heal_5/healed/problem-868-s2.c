#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    const char *end = s + strlen(s);
    const char *p = end - 1;
    
    while (p >= s && isspace((unsigned char)*p)) p--;
    while (p >= s && !isspace((unsigned char)*p)) {
        length++;
        p--;
    }
    return length;
}

int main() {
    const char *str0 = "Hello World      ";
    const char *str1 = "   fly me   to   the moon  ";
    const char *str2 = "luffy is still joyboy";
    
    printf("Length of the last word: %d\n", lengthOfLastWord(str0));
    printf("Length of the last word: %d\n", lengthOfLastWord(str1));
    printf("Length of the last word: %d\n", lengthOfLastWord(str2));
    
    return 0;
}