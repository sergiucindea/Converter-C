#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct{
    int base;
    void (*convert)(char*, int);
} Converter;

extern const struct ConverterClass {
    Converter (*new) ();
} Factory;

#endif
