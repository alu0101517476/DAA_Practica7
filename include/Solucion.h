#pragma once

#include <iostream>
#include <list>
#include <vector>

class Solucion {
 public:
  Solucion() {};
  Solucion(const int& numero_maquinas);
  Solucion(const std::pair<std::vector<std::vector<int>>, int>& solucion): solucion_{solucion} {}
  void agregarTarea(int indice_maquina, int tarea);
  // getters
  std::pair<std::vector<std::vector<int>>, int>& getSolucion() { return solucion_; }
  int getCosteTotal() { return solucion_.second; }
  // setter de coste total
  void setCosteTotal(int coste_total) { solucion_.second = coste_total; }
  // Sobrecarga de operador [] para poder acceder al segundo vector más
  // cómodamente
  std::vector<int>& operator[](const int& indice);
  // Sobrecarga de operador = para poder igualar 2 soluciones
  Solucion operator=(const Solucion& solucion2);
  // Sobrecarga de operador << para imprimir la solución
  friend std::ostream& operator<<(std::ostream& os, const Solucion& Solucion);

 private:
  std::pair<std::vector<std::vector<int>>, int> solucion_;
};

std::ostream& operator<<(std::ostream& os, const Solucion& Solucion);
