#include <stdio.h>
#include "converter.h"

int main() {
    char* inputValue = "#10000";
    Converter converter = newConverter();
    converter.convert(inputValue);
}
