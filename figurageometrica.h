#ifndef FIGURAGEOMETRICA_H_INCLUDED
#define FIGURAGEOMETRICA_H_INCLUDED
#include "scultor.h"

class figuraGeometrica {
protected:
    float r, g, b, a;
public:


    virtual ~figuraGeometrica(){};

    virtual void draw(Sculptor &s)=0;

};

#endif // FIGURAGEOMETRICA_H
