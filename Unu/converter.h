#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct {
    void (*convert)(char*);
} Converter;

static Converter newConverter(void);

#endif
