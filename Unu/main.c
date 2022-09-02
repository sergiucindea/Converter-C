#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "x2f35";
    Converter conv = converter.new();
    conv.convert(inputValue);
}
