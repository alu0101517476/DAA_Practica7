#include "../include/Solucion.h"

void Solucion::agregarTarea(int indice_maquina, int tarea) {
  solucion_[indice_maquina].emplace_back(tarea);
}

std::vector<int> Solucion::operator[](const int& indice) {
  return solucion_[indice];
}
