#include <stdio.h>
#include <string.h>
#include <stddef.h>

char *abbreviate_road(char *str, size_t size) {
    size_t read_pos, write_pos;

    if (str == NULL || size == 0) {
        return NULL;
    }

    write_pos = 0;
    for (read_pos = 0; read_pos < size && str[read_pos] != '\0'; ++read_pos) {
        if (read_pos + 4 <= size && memcmp(str + read_pos, "road", 4) == 0) {
            if (write_pos + 3 < size) {
                str[write_pos++] = 'r';
                str[write_pos++] = 'd';
                str[write_pos++] = '.';
                read_pos += 3;
            } else {
                break;
            }
        } else {
            if (write_pos < size) {
                str[write_pos++] = str[read_pos];
            } else {
                break;
            }
        }
    }

    if (write_pos < size) {
        str[write_pos] = '\0';
    } else if (size > 0) {
        str[size - 1] = '\0';
    }

    return str;
}

int main(void) {
    char input[] = "123 main road and broadway road";

    printf("%s\n", input);
    abbreviate_road(input, sizeof(input));
    printf("%s\n", input);

    return 0;
}