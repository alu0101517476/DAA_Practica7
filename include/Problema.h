#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class Problema {
 public:
  Problema(const std::string& nombre_fichero);

 private:
  int numero_tareas_;
  int numero_maquinas_;
  std::vector<int> tiempo_procesamiento_tareas_;
  std::vector<std::vector<int>> tiempos_setup_;
};