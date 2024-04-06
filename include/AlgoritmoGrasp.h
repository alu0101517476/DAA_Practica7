#pragma once

#include <climits>
#include <random>

#include "Algoritmo.h"
#include "Herramientas.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoGrasp : public Algoritmo {
 public:
  AlgoritmoGrasp(const std::string& nombre_problema)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()} {}
  Solucion resolver();
  int calcularTCTTotal();
  Solucion faseConstructiva();
  Solucion exploracionVecindario();

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};