#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_first_last_equal(const char str[]) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    
    if (len <= 1) {
        return true;
    }
    
    return (str[0] == str[len - 1]);
}

int main() {
    const char str[] = "hello";
    bool result = is_first_last_equal(str);

    printf("%s\n", result ? "true" : "false");

    return 0;
}