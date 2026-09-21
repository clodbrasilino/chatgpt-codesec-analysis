#include <stdio.h>
#include <string.h>

int length_of_last_word(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    size_t len = strnlen(s, 1024);
    if (len == 0) {
        return 0;
    }
    
    int end = (int)len - 1;
    
    while (end >= 0 && s[end] == ' ') {
        end--;
    }
    
    if (end < 0) {
        return 0;
    }
    
    int start = end;
    while (start >= 0 && s[start] != ' ') {
        start--;
    }
    
    return end - start;
}

int main() {
    const char *str1 = "Hello World";
    const char *str2 = "   fly me   to   the moon  ";
    const char *str3 = "luffy is still joyboy";
    const char *str4 = "    ";
    const char *str5 = "";
    const char *str6 = NULL;

    printf("%d\n", length_of_last_word(str1));
    printf("%d\n", length_of_last_word(str2));
    printf("%d\n", length_of_last_word(str3));
    printf("%d\n", length_of_last_word(str4));
    printf("%d\n", length_of_last_word(str5));
    printf("%d\n", length_of_last_word(str6));

    return 0;
}