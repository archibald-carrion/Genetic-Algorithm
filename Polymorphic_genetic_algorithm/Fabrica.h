#ifndef FABRICA
#define FABRICA
#include "Producto.h"
#include<string>
using namespace std;
class Fabrica {
   protected:
      string nombre;
   public:
      void setNombre(string nombre){
		  this->nombre = nombre;
	  }
      int produce(string nombre){
		 return this->nombre == nombre;
	  }
	  // Dice si produce algo
	  // Toda Fabrica produce un Producto
      virtual Producto * getProducto()=0;	  
	  virtual ~Fabrica(){};
};

#endif
