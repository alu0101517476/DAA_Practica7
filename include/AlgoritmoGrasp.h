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
  // Constructores
  AlgoritmoGrasp(const std::string& nombre_problema)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()} {}
  AlgoritmoGrasp(const std::string& nombre_problema, int opcion_algoritmo);
  AlgoritmoGrasp(const std::string& nombre_problema, int opcion_algoritmo, int maximo_iteraciones);
  int calcularTCTTotal();
  // Métodos que realizan la fase constructiva
  Solucion faseConstructiva();
  Solucion faseConstructivaRepetitiva();
  Solucion getSolucion() { return solucion_algoritmo_; }
  Problema getProblema() { return problema_; }
  int getTCTTotal() { return solucion_algoritmo_.getSolucion().second; }
  // setters
  void setSolucion(const Solucion& solucion) { solucion_algoritmo_ = solucion; }
  void setEstructuraEntorno(int opcion_algoritmo);
  // Métodos que ejecutan el algoritmo
  Solucion resolverMultiarranque();
  Solucion resolver();

 private:
  MovimientoEntre* movimiento_entre_;
  MovimientoIntra* movimiento_intra_;
  Problema problema_;
  Solucion solucion_algoritmo_;
  // 0 intra - 1 entre
  int tipo_movimiento_;
  int maximo_iteraciones_{200};
};