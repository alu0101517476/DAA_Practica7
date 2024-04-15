#include "../include/Herramientas.h"

/**
 * @brief Función que calcula cuánto se espera que aumente el TCT total para esa
 * máquina debido a la inserción de una nueva tarea en una posición especifica.
 * No devuelve un TCT nuevo, es el aumento respecto al TCT que ya existia
 * @param solucion solucion actual
 * @param maquina maquina a la que queremos introducirle la tarea
 * @param tarea tarea que queremos introducir a la máquina
 * @param posicion posición en la que queremos introducir la tarea
 * @param procesamiento_tareas vector que contiene el procesamiento de las
 * tareas
 * @param tiempos_setup matriz que contiene los tiempos de setup
 * @return int, el incremento del TCT
 */
int calcularTCTMaquina(const std::vector<int>& maquina,
                       const std::vector<std::vector<int>>& valores_arcos) {
  int resultado{0};
  for (int i{1}; i < maquina.size(); ++i) {
    int trabajo{0};
    trabajo += valores_arcos[maquina[i - 1]][maquina[i]];
    trabajo *= maquina.size() - i;
    resultado += trabajo;
  }
  return resultado;
}

/**
 * @brief Función que calcula el TCT de una máquina después de haber introducido
 * una tarea
 * @param maquina maquina a la que queremos introducirle una tarea
 * @param posicion posición en la que queremos introducir la tarea
 * @param tarea tarea que vamos a introducir
 * @param solucion_algoritmo solución actual
 * @param valores_arcos valores de todos los arcos
 * @return int
 */
int calcularTCTOptimo(int maquina, int posicion, int tarea,
                      Solucion& solucion_algoritmo,
                      const std::vector<std::vector<int>>& valores_arcos) {
  std::vector<int> auxiliar_tarea{
      solucion_algoritmo.getSolucion().first[maquina]};
  auxiliar_tarea.emplace(auxiliar_tarea.begin() + posicion + 1, tarea);
  int tct_resultado{calcularTCTMaquina(auxiliar_tarea, valores_arcos)};
  return tct_resultado;
}

/**
 * @brief Función que calcula el TCT total
 * @param solucion_algoritmo
 * @param valores_arcos
 * @return int
 */
int calcularTCTTotalMaquinas(
    Solucion& solucion_algoritmo,
    const std::vector<std::vector<int>>& valores_arcos) {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, valores_arcos);
  }
  return tct_total;
}

/**
 * @brief Sibrecarga de función para calcular el TCT total pero dado una
 * estructura de datos diferente a la clase Solución
 * @param matriz_solucion
 * @param valores_arcos
 * @return int
 */
int calcularTCTTotalMaquinas(
    std::vector<std::vector<int>>& matriz_solucion,
    const std::vector<std::vector<int>>& valores_arcos) {
  int tct_total{0};
  for (const auto& maquina : matriz_solucion) {
    tct_total += calcularTCTMaquina(maquina, valores_arcos);
  }
  return tct_total;
}

/**
 * @brief Función que se ejecuta previamente antes de ejecutar el algoritmo
 * GRASP, para obtener mediante consola la estructura de entorno que quiera usar
 * el usuario para ejecutar el algoritmo
 * @return int la estructura de entorno que quiere utilizar el usuario
 */
int elegirEstructuraEntornoGrasp() {
  std::cout
      << "Elige la estructura de entorno con la que quieres ejecutar grasp:"
      << std::endl;
  std::cout << "1. Intercambio de tareas entre máquinas" << std::endl;
  std::cout << "2. Intercambio de tareas en la misma máquina" << std::endl;
  std::cout << "3. Re-inserción de tareas entre máquinas" << std::endl;
  std::cout << "4. Re-inserción de tareas en la misma máquina" << std::endl;
  int opcion;
  std::cin >> opcion;
  if (opcion != 1 || opcion != 2 || opcion != 3 || opcion != 4) return opcion;
  std::cout << "Error, la opción '" << opcion << "' no es válida" << std::endl;
  exit(1);
}

/**
 * @brief Función que imprime por pantalla la ayuda del programa
 */
void ayuda() {
  std::cout << "El uso del programa es el siguiente: " << std::endl;
  std::cout << "./TCT" << std::endl;
}