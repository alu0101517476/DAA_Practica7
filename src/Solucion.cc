#include "../include/Solucion.h"

Solucion::Solucion(const int& numero_maquinas) {
  std::vector<std::vector<int>> aux(numero_maquinas, std::vector<int>(0));
  solucion_.first = aux;
  solucion_.second = 0;
}

void Solucion::agregarTarea(int indice_maquina, int tarea) {
  solucion_.first[indice_maquina].emplace_back(tarea);
}

std::vector<int>& Solucion::operator[](const int& indice) {
  return solucion_.first[indice];
}

std::ostream& operator<<(std::ostream& os, const Solucion& solucion) {
  std::cout << solucion.solucion_.second << std::endl;
  for (int i{0}; i < solucion.solucion_.first.size(); ++i) {
    os << i << ": ";
    for (const auto& tarea : solucion.solucion_.first[i]) {
      if (tarea != 0) os << tarea << " | ";
    }
    os << std::endl;
  }
  return os;
}