#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class Problema {
 public:
  Problema(const std::string& nombre_fichero);
  // getters
  std::vector<int> getTiempoProcesamientoTareas();
  std::vector<std::vector<int>> getTiemposSetup();
  std::vector<std::vector<int>> getValoresArcos();
  int getNumeroMaquinas() { return numero_maquinas_; }
  int getNumeroTareas() { return numero_tareas_; }
  // Sobrecarga de operador << para poder imprimir el problema
  friend std::ostream& operator<<(std::ostream& os, const Problema& problema);

 private:
  int numero_tareas_; // n
  int numero_maquinas_; // m
  std::vector<int> tiempo_procesamiento_tareas_; // pj
  std::vector<std::vector<int>> tiempos_setup_; // sij
  std::vector<std::vector<int>> valores_arcos_; // tij
};

std::ostream& operator<<(std::ostream& os, const Problema& problema);