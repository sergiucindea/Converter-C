#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct{
    void (*convert)(char*, int);
} Converter;

typedef struct {
    Converter(*newInstance) ();
} ConverterFactory;

extern const ConverterFactory Factory;

#endif
