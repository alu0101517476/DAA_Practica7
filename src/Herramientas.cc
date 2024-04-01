#include "../include/Herramientas.h"

/**
 * @brief Función que calcula cuánto se espera que aumente el TCT total para esa
 * máquina debido a la inserción de una nueva tarea en una posición especifica.
 * No devuelve un TCT nuevo, es el aumento respecto al TCT que ya existia
 * @param solucion solucion actual
 * @param maquina maquina a la que queremos introducirle la tarea
 * @param tarea tarea que queremos introducir a la máquina
 * @param posicion posición en la que queremos introducir la tarea
 * @param procesamiento_tareas vector que contiene el procesamiento de las tareas
 * @param tiempos_setup matriz que contiene los tiempos de setup
 * @return int, el incremento del TCT 
 */
int calcularTCTMaquina(const std::vector<int>& maquina, const std::vector<std::vector<int>>& valores_arcos) {
  int resultado{0};
  for (int i{1}; i < maquina.size(); ++i) {
    int trabajo{0};
    trabajo += valores_arcos[maquina[i - 1]][maquina[i]];
    trabajo *= maquina.size() - i;
    resultado += trabajo;
  }
  return resultado;
}

int calcularTCTOptimo(int maquina, int posicion, int tarea, Solucion& solucion_algoritmo, const std::vector<std::vector<int>>& valores_arcos) {
  std::vector<int> auxiliar_tarea{solucion_algoritmo.getSolucion().first[maquina]};
  auxiliar_tarea.emplace(auxiliar_tarea.begin() + posicion + 1, tarea);
  int tct_resultado{calcularTCTMaquina(auxiliar_tarea, valores_arcos)};
  return tct_resultado;
}

/**
 * @brief Función que imprime por pantalla la ayuda del programa
 */
void ayuda() {
  std::cout << "El uso del programa es el siguiente: " << std::endl;
  std::cout << "./TCT ruta de la instancia del problema" << std::endl;
}