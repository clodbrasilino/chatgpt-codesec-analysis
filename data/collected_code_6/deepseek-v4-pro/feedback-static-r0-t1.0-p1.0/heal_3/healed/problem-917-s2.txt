#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *sequence;
    int start;
    int length;
} Sequence;

Sequence *find_sequences(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int len = (int)strlen(str);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    Sequence *sequences = NULL;
    *count = 0;

    for (int i = 0; i < len - 1; i++) {
        if (isupper((unsigned char)str[i]) && islower((unsigned char)str[i + 1])) {
            int j = i + 1;
            while (j < len && islower((unsigned char)str[j])) {
                j++;
            }

            int length = j - i;
            if (length < 1) {
                continue;
            }

            Sequence *temp = (Sequence *)realloc(sequences, ((size_t)(*count) + 1) * sizeof(Sequence));
            if (temp == NULL) {
                for (int k = 0; k < *count; k++) {
                    free(sequences[k].sequence);
                }
                free(sequences);
                *count = 0;
                return NULL;
            }
            sequences = temp;

            sequences[*count].sequence = (char *)malloc((size_t)length + 1);
            if (sequences[*count].sequence == NULL) {
                for (int k = 0; k < *count; k++) {
                    free(sequences[k].sequence);
                }
                free(sequences);
                *count = 0;
                return NULL;
            }

            if ((size_t)(i + length) <= (size_t)len) {
                memcpy(sequences[*count].sequence, &str[i], (size_t)length);
                sequences[*count].sequence[length] = '\0';
                sequences[*count].start = i;
                sequences[*count].length = length;
                (*count)++;
            } else {
                free(sequences[*count].sequence);
                for (int k = 0; k < *count; k++) {
                    free(sequences[k].sequence);
                }
                free(sequences);
                *count = 0;
                return NULL;
            }

            i = j - 1;
        }
    }

    return sequences;
}

void free_sequences(Sequence *sequences, int count) {
    if (sequences != NULL) {
        for (int i = 0; i < count; i++) {
            free(sequences[i].sequence);
        }
        free(sequences);
    }
}

int main(void) {
    const char *text = "Hello World This Is A Test Example";
    int count = 0;
    Sequence *result = find_sequences(text, &count);

    if (result == NULL && count > 0) {
        return 1;
    }

    if (result != NULL) {
        printf("Found %d sequences:\n", count);
        for (int i = 0; i < count; i++) {
            printf("Sequence: \"%s\" at position %d, length %d\n",
                   result[i].sequence, result[i].start, result[i].length);
        }
    } else {
        printf("No sequences found or memory allocation failed.\n");
    }

    free_sequences(result, count);
    return 0;
}