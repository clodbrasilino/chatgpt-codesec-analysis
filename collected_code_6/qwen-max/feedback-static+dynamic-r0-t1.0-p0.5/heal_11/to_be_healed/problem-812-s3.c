#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            size_t len1 = strnlen(pos + 4, 100);
            size_t len2 = strnlen(str, 100);
            if (len1 + 3 < (size_t)(len2 - (pos - str))) {
                memmove(pos + 3, pos + 4, len1 + 1);
                if (len1 + 3 < (size_t)(len2 - (pos - str))) {
                    /* Possible weaknesses found:
                     *  Assignment 'remaining_len=len2-(pos-str)-4+3', assigned value is greater than 2
                     */
                    size_t remaining_len = len2 - (pos - str) - 4 + 3;
                    /* Possible weaknesses found:
                     *  Condition 'remaining_len>=3' is always true [knownConditionTrueFalse]
                     *  Condition 'remaining_len>=3' is always true
                     */
                    if (remaining_len >= 3) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(pos, "rd", 2);
                        pos[2] = '.';
                        str = pos + 3;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
        } else {
            str = pos + 1;
        }
    }
}

int main() {
    char input[] = "Please use the road to get to the next road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}