#include <stdio.h>
#include <string.h>

char* removeParenthesis(char* str) {
    int open = 0;
    char *p = str;
    char *q = str;
    while(*p) {
        if (*p == '(') {
            ++open;
        } else if (*p == ')' && open) {
            --open;
        } else if (!open) {
            *q++ = *p;
        }
        ++p;
    }
    *q = '\0';
    return str;
}

int main() {
    char str[] = "Hello (world)";
    printf("%s\n", removeParenthesis(str));
    return 0;
}