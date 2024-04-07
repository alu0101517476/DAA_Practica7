#include "../include/Solucion.h"

/**
 * @brief Constructor de la clase solución que dado un número de máquinas,
 * genera la solución con un vector vacío
 * @param numero_maquinas
 */
Solucion::Solucion(const int& numero_maquinas) {
  std::vector<std::vector<int>> aux(numero_maquinas, std::vector<int>(0));
  solucion_.first = aux;
  solucion_.second = 0;
}

/**
 * @brief Método que permite agregar una tarea al final de una maquina
 * @param indice_maquina indice de la máquina a la que queremos insertar la
 * tarea
 * @param tarea tarea que queremos insertar
 */
void Solucion::agregarTarea(int indice_maquina, int tarea) {
  solucion_.first[indice_maquina].emplace_back(tarea);
}

/**
 * @brief Sobrecarga de operador [] que nos permite acceder a una máquina de
 * manera más cómoda
 * @param indice indice de la máquina
 * @return std::vector<int>&
 */
std::vector<int>& Solucion::operator[](const int& indice) {
  return solucion_.first[indice];
}

/**
 * @brief Sobrecarga de operador = para poder igualar 2 soluciones
 * @param solucion2 segunda solución a la que queremos igualar la solución de la
 * izquierda
 * @return Solucion
 */
Solucion Solucion::operator=(Solucion& solucion2) {
  solucion_ = solucion2.solucion_;
  return *this;
}

/**
 * @brief Sobrecarga de operador << para poder imprimir una solución
 * @param os
 * @param solucion solución que queremos imprimir
 * @return std::ostream&
 */
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