#pragma once

#include <climits>
#include <random>

#include "../include/Algoritmos_vecindario/IntercambioEntre.h"
#include "../include/Algoritmos_vecindario/IntercambioIntra.h"
#include "../include/Algoritmos_vecindario/MovimientoEntre.h"
#include "../include/Algoritmos_vecindario/MovimientoIntra.h"
#include "../include/Algoritmos_vecindario/ReinsercionEntre.h"
#include "../include/Algoritmos_vecindario/ReinsercionIntra.h"
#include "Algoritmo.h"
#include "Herramientas.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoGrasp : public Algoritmo {
 public:
  AlgoritmoGrasp(const std::string& nombre_problema)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()} {}
  AlgoritmoGrasp(const std::string& nombre_problema, int opcion_algoritmo);
  AlgoritmoGrasp(const std::string& nombre_problema, int opcion_algoritmo, int maximo_iteraciones);
  void setEstructuraEntorno(int opcion_algoritmo);
  Solucion resolver();
  int calcularTCTTotal();
  Solucion faseConstructiva();
  Solucion getSolucion() { return solucion_algoritmo_; }

 private:
  MovimientoEntre* movimiento_entre_;
  MovimientoIntra* movimiento_intra_;
  Problema problema_;
  Solucion solucion_algoritmo_;
  // 0 intra - 1 entre
  int tipo_movimiento_;
  int maximo_iteraciones_{200};
};