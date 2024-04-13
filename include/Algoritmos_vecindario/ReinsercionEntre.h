#pragma once

#include "Herramientas.h"
#include "MovimientoEntre.h"
#include "Problema.h"
#include "Solucion.h"

class ReinsercionEntre : public MovimientoEntre {
 public:
  ReinsercionEntre(const Solucion& solucion_fase_constructiva)
      : solucion_fase_constructiva_{solucion_fase_constructiva} {};
  Solucion explorarVecindario(const std::vector<std::vector<int>>& valores_arcos, int numero_maximo_intentos = 10);
  void setSolucion(const Solucion& solucion) override { solucion_fase_constructiva_ = solucion; }
  Solucion& getSolucion() { return solucion_fase_constructiva_; }
  void imprimirSolucion();

 private:
  bool solucionEncontrada_(std::vector<int>& maquina1,
                           std::vector<int>& maquina2,
                           const std::vector<std::vector<int>>& valores_arcos);
  Solucion solucion_fase_constructiva_;
};