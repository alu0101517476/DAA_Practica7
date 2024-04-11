#pragma once

#include <climits>
#include <random>

#include "../include/Algoritmos_vecindario/MovimientoIntra.h"
#include "../include/Algoritmos_vecindario/MovimientoEntre.h"
#include "../include/Algoritmos_vecindario/ReinsercionIntra.h"
#include "../include/Algoritmos_vecindario/ReinsercionEntre.h"
#include "../include/Algoritmos_vecindario/IntercambioIntra.h"
#include "../include/Algoritmos_vecindario/IntercambioEntre.h"
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
  Solucion getSolucion() { return solucion_algoritmo_; }

 private:
  MovimientoEntre* movimiento_entre_;
  MovimientoIntra* movimiento_intra_;
  Problema problema_;
  Solucion solucion_algoritmo_;
};