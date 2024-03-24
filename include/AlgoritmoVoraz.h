#pragma once

#include "Algoritmo.h"

class AlgoritmoVoraz : public Algoritmo {
 public:
  AlgoritmoVoraz(const std::string& nombre_algoritmo) : problema_{nombre_algoritmo} {};

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};