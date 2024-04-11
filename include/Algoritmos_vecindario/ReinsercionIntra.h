#pragma once

#include "MovimientoIntra.h"
#include "Problema.h"
#include "Solucion.h"

class ReinsercionIntra : public MovimientoIntra {
 public:
  ReinsercionIntra(const Solucion& solucion_fase_constructiva)
      : solucion_fase_constructiva_{solucion_fase_constructiva} {};
  Solucion explorarVecindario(const Problema& problema,
                              int numero_maximo_intentos = 10);

 private:
  bool solucionEncontrada_(std::vector<int>& maquina, const Problema& problema);
  Solucion solucion_fase_constructiva_;
};