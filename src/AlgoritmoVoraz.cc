#include "../include/AlgoritmoVoraz.h"

Solucion AlgoritmoVoraz::resolver() {
  // Seleccionamos las m tareas con menores valores de t0j
  for (int j{0}; j < problema_.getNumeroMaquinas(); ++j) {
    solucion_algoritmo_.agregarTarea(j, problema_.getValoresArcos()[0][j]); 
  }

}