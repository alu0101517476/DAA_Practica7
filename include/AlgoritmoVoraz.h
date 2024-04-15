#pragma once

#include <climits>

#include "Algoritmo.h"
#include "Herramientas.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoVoraz : public Algoritmo {
 public:
  AlgoritmoVoraz(const std::string& nombre_problema)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()} {};
  // Método que nos permite calcular el TCT total
  int calcularTCTTotal();
  // Método que ejecuta el algoritmo voraz
  Solucion resolver();
  // getters
  Problema getProblema() { return problema_; }
  int getTCTTotal() { return solucion_algoritmo_.getSolucion().second; }

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};