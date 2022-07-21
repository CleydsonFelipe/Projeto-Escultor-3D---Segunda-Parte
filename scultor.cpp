#include  "scultor.h"
#include  <iostream>
#include  <fstream>
#include  <string>
#include  <iomanip>
#include  <math.h>
#include  <vector>
using  namespace  std;

/**
*
*@brief Metodo Construtor
*@param int _nx, int _ny, int _nz
*
*/
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // Alocação dinâmica da matriz 3d
    v = new Voxel**[nx];
     for (int i = 0; i<nx; i++){
      v[i] = new Voxel*[ny];
       }
  
     for (int i = 0; i<nx; i++){
       for(int j = 0; j<ny; j++){
       v[i][j]= new Voxel[nz];
      }
    }

  
	  for (int i = 0 ; i < nx; i++) { // Atribuindo valores iniciais
		  for (int j = 0 ; j < ny; j++) {
			  for (int k = 0 ; k < nz; k++) {
				v[i][j][k].isOn = false ;
				v[i][j][k].r = 0 ;
				v[i][j][k].g = 0 ;
				v[i][j][k].b = 0 ;
				v[i][j][k].a = 0 ;
			}
		}
	}
}
/**
*
*@brief Metodo Destrutor
*@param int i, int j
*
*/

Sculptor::~Sculptor (){
    for (int i = 0; i < nx; i++){
        for (int j = 0 ; j < ny; j++){
               delete[] v[i][j];
            }
        }
        for (int i= 0; i <nx; i++){
            delete[] v[i];
        }
    delete[] v;
  }
/**
*
*@brief Metodo Definição de cor
*@param float r, float g, float b, float alpha
*
*/
void  Sculptor::setColor (float r, float g, float b, float alpha) // define uma cor e transparência de cada voxel
{
    this ->r = r/255;
    this ->g = g/255;
    this ->b = b/255;
    this ->a = alpha;
}
/**
*
*@brief Metodo Constrtutor de voxel
*@param int x, int y, int z
*
*/
void  Sculptor::putVoxel (int x, int y, int z){
    v[x][y][z].isOn = true ;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;    

}
/**
*
*@brief Metodo Destrtutor de voxel
*@param int x, int y, int z
*
*/
void  Sculptor::cutVoxel (int x, int y, int z){
    v[x][y][z].isOn = false ;
}
void  Sculptor::writeOFF(const char *filename)
{
  int quantvox = 0 ;
  int ref;
  ofstream Arqfinal;
  Arqfinal.open (filename);

  Arqfinal<< "OFF \n " ;

  // varre todos os voxel e analisa os que devem ser exibidos no .off
  for (int i = 0; i < nx; i++){
      for (int j = 0; j <ny; j++){
           for (int k = 0; k <nz; k++){
                if (v[i][j][k].isOn == true){
                quantvox++;
                }
           }
       }
  }
  Arqfinal<<quantvox * 8 << "  " <<quantvox * 6 << "  " << "0" << "\n" ; // mostra a quantidade total de vértices, faces e arestas

  for (int a = 0 ; a < nx; a++){
      for (int b = 0 ; b < ny; b++){
           for (int c = 0 ; c < nz; c++){
                if (v[a][b][c].isOn == true ){
                Arqfinal << a - 0.5 << "  " << b + 0.5 << "  " << c - 0.5 << endl;
                Arqfinal << a - 0.5 << "  " << b - 0.5 << "  " << c - 0.5 << endl;
                Arqfinal << a + 0.5 << "  " << b - 0.5 << "  " << c - 0.5 << endl;
                Arqfinal << a + 0.5 << "  " << b + 0.5 << "  " << c - 0.5 << endl;
                Arqfinal << a - 0.5 << "  " << b + 0.5 << "  " << c + 0.5 << endl;
                Arqfinal << a - 0.5 << "  " << b - 0.5 << "  " << c + 0.5 << endl;
                Arqfinal << a + 0.5 << "  " << b - 0.5 << "  " << c + 0.5 << endl;
                Arqfinal << a + 0.5 << "  " << b + 0.5 << "  " << c + 0.5 << endl;
                }
           }
      }
  }

  quantvox = 0 ;

  // descreve cada voxel
  for (int a= 0 ; a<nx; a++){
      for (int b = 0 ; b<ny; b++){
           for (int c= 0 ; c<nz; c++){
                if(v[a][b][c]. isOn == true ){
                ref = quantvox * 8 ;
                Arqfinal << fixed;

                // montar linha que realiza a construção das faces a partir dos vértices e mostrar como propriedades rgba do voxel
                Arqfinal << "4" << "  " << 0+ref << "  " << 3+ref << "  " << 2+ref << "  " << 1+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                Arqfinal << "4" << "  " << 4+ref << "  " << 5+ref << "  " << 6+ref << "  " << 7+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                Arqfinal << "4" << "  " << 0+ref << "  " << 1+ref << "  " << 5+ref << "  " << 4+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                Arqfinal << "4" << "  " << 0+ref << "  " << 4+ref << "  " << 7+ref << "  " << 3+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                Arqfinal << "4" << "  " << 3+ref << "  " << 7+ref << "  " << 6+ref << "  " << 2+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                Arqfinal << "4" << "  " << 1+ref << "  " << 2+ref << "  " << 6+ref << "  " << 5+ref << "  " ;
                Arqfinal << setprecision(2)<<v[a][b][c]. r << "  " << setprecision (2)<<v[a][b][c]. g << "  " << setprecision (2)<<v[a][b][c]. b << "  " << setprecision (2) << v[a][b][c]. a << " \n " ;

                quantvox = quantvox + 1 ;
                }
           }
       }
  }
  Arqfinal.close();
}
