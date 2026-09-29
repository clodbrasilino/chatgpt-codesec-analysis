#include <stdio.h>
#include <stdbool.h>

bool checkDataType(int tuple[], int size) {
   for (int i = 0; i < size - 1; i++) {
      if (sizeof(tuple[i]) != sizeof(tuple[i + 1]))
         return false;
   }
   return true;
}