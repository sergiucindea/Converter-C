#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "2fe7";
    int inputBase = 19;
    Converter conv = Factory.new();
    conv.convert(inputValue, inputBase);
}
