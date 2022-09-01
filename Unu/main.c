#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "xf3";
    Converter converter = newConverter();
    converter.convert(inputValue);
}
