#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "12265";
    Converter conv = Factory.new();
    conv.convert(inputValue);
}
