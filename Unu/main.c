#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "2fe7";
    int inputBase = 0;
    printf("Please enter a conversion base between 2 and 36:\n");
    scanf("%d", &inputBase);
    if (inputBase < 2 || inputBase > 36) {
        printf("Conversion to input base is not possible");
    } else {
        Converter conv = Factory.new();
        conv.convert(inputValue, inputBase);
    }
}
