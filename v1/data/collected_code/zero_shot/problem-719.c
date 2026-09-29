#include <stdbool.h>

bool matchString(char *str) {
    if (str[0] == 'a') {
        int i = 1;
        while (str[i] == 'b') {
            i++;
        }
        return true;
    }
    return false;
}