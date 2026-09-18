#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_max_uppercase_run(const char* str) {
    int max_run = 0, current_run = 0;
    for (int i = 0; str[i]; i++) {
        if (isupper(str[i])) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    return max_run;
}

int main() {
    const char *str = "HeLLooWoRLDiiiAAAAMMmmmMMmN";
    printf("Max run of uppercase characters: %d\n", get_max_uppercase_run(str));
    return 0;
}