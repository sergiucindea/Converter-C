#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct{
    void (*convert)(char*);
} Converter;

extern const struct ConverterClass {
    Converter (*new) ();
} Factory;

#endif
