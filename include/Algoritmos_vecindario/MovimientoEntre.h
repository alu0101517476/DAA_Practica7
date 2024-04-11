#pragma once

#include <vector>

#include "Solucion.h"

class MovimientoEntre {
 public:
  virtual Solucion explorarVecindario(
      const std::vector<std::vector<int>>& valores_arcos,
      int numero_maximo_intentos = 10) = 0;

 private:
  virtual bool solucionEncontrada_(
      std::vector<int>& maquina1, std::vector<int>& maquina2,
      const std::vector<std::vector<int>>& valores_arcos) = 0;
};