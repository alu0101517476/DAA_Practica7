#include "../include/Problema.h"

Problema::Problema(const std::string& nombre_fichero) {
  std::ifstream fichero_problema{nombre_fichero, std::ios::in};
  if (fichero_problema.fail()) {
    std::cerr << "Error, el fichero " << nombre_fichero
              << " no se pudo abrir correctamente" << std::endl;
    exit(1);
  }
  std::string linea;
  // Leemos el número de tareas
  std::getline(fichero_problema, linea);
  linea = linea.substr(linea.find(':') + 1, linea.size() - 1);
  std::stringstream linea_aux{linea};
  linea_aux >> numero_tareas_;
  // Leemos el número de maquinas
  std::getline(fichero_problema, linea);
  linea = linea.substr(linea.find(':') + 1, linea.size() - 1);
  linea_aux.str("");
  linea_aux.clear();
  linea_aux << linea;
  linea_aux >> numero_maquinas_;
  // Leemos el tiempo de procesamiento de cada tarea
  std::getline(fichero_problema, linea);
  linea = linea.substr(linea.find(']') + 1, linea.size() - 1);
  linea_aux.str("");
  linea_aux.clear();
  linea_aux << linea;
  int procesamiento_tarea;
  while (linea_aux >> procesamiento_tarea) {
    tiempo_procesamiento_tareas_.emplace_back(procesamiento_tarea);
  }
  std::vector<std::vector<int>> aux{numero_tareas_ + 1,
                                    std::vector<int>(numero_tareas_ + 1)};
  tiempos_setup_ = aux;
  std::getline(fichero_problema, linea);
  // Leemos y almacenamos los tiempos de setup
  for (int i = 0; i <= numero_tareas_ && std::getline(fichero_problema, linea);
       ++i) {
    std::istringstream tiempo_setup(linea);
    for (int j = 0; j <= numero_tareas_; ++j) {
      tiempo_setup >> tiempos_setup_[i][j];
    }
  }
}