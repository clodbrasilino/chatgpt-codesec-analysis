#include <stdio.h>
#include <string.h>

void find_substrings(const char *str, const char *sub) {
    if (str == NULL || sub == NULL || *sub == '\0') {
        return;
    }
    
    const char *pos = str;
    /* Possible weaknesses found:
     *  Value stored to 'sub_len' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'sub_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t sub_len = strlen(sub);
    int found = 0;
    
    while ((pos = strstr(pos, sub)) != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Found at index: %ld\n", pos - str);
        pos++;
        found = 1;
    }
    
    if (!found) {
        printf("Substring not found\n");
    }
}

int main(void) {
    const char *str = "hello world, hello universe, hello again";
    const char *sub = "hello";
    
    printf("String: %s\n", str);
    printf("Substring: %s\n", sub);
    find_substrings(str, sub);
    
    return 0;
}