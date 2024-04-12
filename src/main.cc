#include <iostream>
#include <sstream>

#include "../include/Algoritmo.h"
#include "../include/AlgoritmoVoraz.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"
#include "../include/AlgoritmoGrasp.h"

int main(int argc, char* argv[]) { 
  if (argc != 2) {
    std::cerr << "Error: número de argumentos incorrecto" << std::endl;
    ayuda();
    return 1;
  }
  AlgoritmoVoraz voraz{std::string(argv[1])};
  std::cout << voraz.resolver() << std::endl;
  std::cout << "-----------------" << std::endl;
  elegirEstructuraEntornoGrasp();
  AlgoritmoGrasp grasp{std::string(argv[1])};
  std::cout << grasp.resolver() << std::endl;
  return 0; 
}