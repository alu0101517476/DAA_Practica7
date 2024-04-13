#pragma once

#include <vector>

#include "../include/Herramientas.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"

class MovimientoIntra {
 public:
  virtual Solucion explorarVecindario(const Problema& problema,
                                      int numero_maximo_intentos) = 0;
  virtual void setSolucion(const Solucion& solucion) = 0;
  virtual Solucion& getSolucion() = 0;
  virtual void imprimirSolucion() = 0;

 private:
  virtual bool solucionEncontrada_(std::vector<int>& maquina,
                                   const Problema& problema) = 0;
};