#include <iostream>
#include <sstream>

#include "../include/Algoritmo.h"
#include "../include/AlgoritmoVoraz.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"

int main(int argc, char* argv[]) { 
  if (argc != 2) {
    std::cerr << "Error: número de argumentos incorrecto" << std::endl;
    ayuda();
    return 1;
  }
  AlgoritmoVoraz voraz{std::string(argv[1])};
  std::cout << voraz.resolver() << std::endl;
  return 0; 
}