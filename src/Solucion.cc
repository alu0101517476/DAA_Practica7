#include "../include/Solucion.h"

void Solucion::agregarTarea(int indice_maquina, int tarea) {
  solucion_[indice_maquina].emplace_back(tarea);
}

std::vector<int> Solucion::operator[](const int& indice) {
  return solucion_[indice];
}

std::ostream& operator<<(std::ostream& os, const Solucion& solucion) {
  for (int i{0}; i < solucion.solucion_.size(); ++i) {
    os << i << ": ";
    for (const auto& tarea : solucion.solucion_[i]) {
      os << tarea << " | ";
    }
    os << std::endl;
  }
  return os;
}