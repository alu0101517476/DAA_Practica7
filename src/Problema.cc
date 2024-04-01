#include "../include/Problema.h"

std::vector<int> Problema::getTiempoProcesamientoTareas() {
  return tiempo_procesamiento_tareas_;
}

std::vector<std::vector<int>> Problema::getTiemposSetup() {
  return tiempos_setup_;
}

std::vector<std::vector<int>> Problema::getValoresArcos() {
  return valores_arcos_;
}

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
  // leemos la linea "Sij:U[]"
  std::getline(fichero_problema, linea);
  // Leemos y almacenamos los tiempos de setup
  for (int i = 0; i <= numero_tareas_ && std::getline(fichero_problema, linea);
       ++i) {
    std::stringstream tiempo_setup(linea);
    for (int j = 0; j <= numero_tareas_; ++j) {
      tiempo_setup >> tiempos_setup_[i][j];
    }
  }
  valores_arcos_ = aux;
  // Calculamos los valores de los arcos
  for (size_t i = 0; i < tiempos_setup_.size(); ++i) {
    for (size_t j = 0; j < tiempos_setup_[i].size(); ++j) {
      // Calcula tij directamente para todas las transiciones
      valores_arcos_[i][j] = tiempos_setup_[i][j] + tiempo_procesamiento_tareas_[j];  // Acceso directo a pj con j
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Problema& problema) {
  std::cout << "n: " << problema.numero_tareas_ << std::endl;
  std::cout << "m: " << problema.numero_maquinas_ << std::endl;
  std::cout << "Pi: ";
  for (const auto& tiempo_procesamiento : problema.tiempo_procesamiento_tareas_) {
    std::cout << tiempo_procesamiento << ' ';
  }
  std::cout << std::endl;
  std::cout << "Sij: " << std::endl;
  std::cout << problema.tiempos_setup_.size() << ' ' << problema.tiempos_setup_[0].size() << std::endl;
  for (const auto& maquina : problema.tiempos_setup_) {
    for (const auto& tiempo_setup_maquina : maquina) {
      std::cout << tiempo_setup_maquina << ' ';
    }
    std::cout << std::endl;
  }
  return os;
}