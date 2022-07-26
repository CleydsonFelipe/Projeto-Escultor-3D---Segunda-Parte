#include <iostream>
#include "scultor.h"
#include "interpretador.h"
#include "putVoxel.h"
#include "putBox.h"
#include "putSphere.h"
#include "putEllipsoid.h"
#include "cutVoxel.h"
#include "cutBox.h"
#include "cutSphere.h"
#include "cutEllipsoid.h"

using namespace std;

int main()
{
    Sculptor *s1;

    Interpretador parser;

    std::vector<figuraGeometrica*> figs;
  
    figs = parser.parse("entrada.txt");

    s1 = new Sculptor(parser.getDimx(), parser.getDimy(), parser.getDimz());

    for(size_t i=0; i<figs.size(); i++){
        std::cout << "draw\n";
        figs[i]->draw(*s1);
    }

    s1->writeOFF((char*)"gato.off");

    for(size_t i=0; i<figs.size(); i++){
        delete figs[i];
    }
    delete s1;
    return 0;
}
