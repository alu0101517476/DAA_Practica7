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
#include "AlgoritmoGrasp.h"

class AlgoritmoGvns : public Algoritmo {
 public:
  // Constructores
  AlgoritmoGvns(const std::string& nombre_problema)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()} {}
  AlgoritmoGvns(const std::string& nombre_problema, int maximo_iteraciones)
      : problema_{nombre_problema},
        solucion_algoritmo_{problema_.getNumeroMaquinas()},
        maximo_iteraciones_{maximo_iteraciones} {}
  // Métodos que ejecutan el algoritmo
  Solucion resolver();
  Solucion resolverMultiArranque();
  int calcularTCTTotal();
  // getters
  Problema getProblema() { return problema_; }
  int getTCTTotal() { return solucion_algoritmo_.getSolucion().second; }

 private:
  // Método que ejecuta el algoritmo VND
  Solucion VND_(const Solucion& solucion);
  // Métodos que realizan las perturbaciones
  Solucion perturbacionAleatoria_(const Solucion& solucion);
  Solucion perturbacion_(const Solucion& solucion);
  // Atributos de la clase
  Solucion solucion_algoritmo_;
  int maximo_iteraciones_{200};
  Problema problema_;
};