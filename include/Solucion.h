#pragma once

#include <iostream>
#include <list>
#include <vector>

class Solucion {
 public:
  Solucion() {};
  void agregarTarea(int indice_maquina, int tarea);
  // getters
  std::vector<std::vector<int>> getSolucion() { return solucion_; }
  // Sobrecarga de operador [] para poder acceder al segundo vector más
  // cómodamente
  std::vector<int> operator[](const int& indice);
  // Sobrecarga de operador << para imprimir la solución
  friend std::ostream& operator<<(std::ostream& os, const Solucion& Solucion);

 private:
  std::vector<std::vector<int>> solucion_;
};

std::ostream& operator<<(std::ostream& os, const Solucion& Solucion);
