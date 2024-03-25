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

 private:
  int numero_tareas_;
  int numero_maquinas_;
  std::vector<int> tiempo_procesamiento_tareas_;
  std::vector<std::vector<int>> tiempos_setup_;
  std::vector<std::vector<int>> valores_arcos_;
};