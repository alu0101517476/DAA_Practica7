#pragma once

#include <climits>

#include "Algoritmo.h"
#include "Herramientas.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoVoraz : public Algoritmo {
 public:
  AlgoritmoVoraz(const std::string& nombre_problema)
      : problema_{nombre_problema}, solucion_algoritmo_{} {};

  Solucion resolver();

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};