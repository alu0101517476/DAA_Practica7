#include <iostream>
#include <sstream>

#include "../include/Algoritmo.h"
#include "../include/AlgoritmoVoraz.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"

int main() { 
  AlgoritmoVoraz voraz{"PMSP/I40j_2m_S1_1.txt"};
  std::cout << voraz.resolver() << std::endl;
  return 0; 
}