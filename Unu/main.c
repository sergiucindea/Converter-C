#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "2f";
    int inputBase = 0;
    printf("Please enter a conversion base between 2 and 36:\n");
    scanf("%d", &inputBase);
    if (inputBase < 2 || inputBase > 36) {
        printf("Conversion to input base is not possible");
    } else {
        Converter conv = Factory.newInstance();
        conv.convert(inputValue, inputBase);
    }
}
