#pragma once

#include "Algoritmo.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoVoraz : public Algoritmo {
 public:
  AlgoritmoVoraz(const std::string& nombre_algoritmo) : problema_{nombre_algoritmo} {};

  Solucion resolver();
 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};