#include <stdbool.h>

bool matchString(const char* str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') {
            count++;
        }
        else if (str[i] == 'b') {
            if (count == 1 || count == 3) {
                count++;
            }
        }
        else {
            count = 0;
        }
    }
    return (count == 4);
}