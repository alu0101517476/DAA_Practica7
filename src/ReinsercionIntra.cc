#include "../include/Algoritmos_vecindario/ReinsercionIntra.h"

/**
 * @brief Método que imprime la solución del problema
 */
void ReinsercionIntra::imprimirSolucion() {
  std::cout << solucion_fase_constructiva_.getSolucion().second << std::endl;
  for (int i{0}; i < solucion_fase_constructiva_.getSolucion().first.size();
       ++i) {
    std::cout << i << ": ";
    for (const auto& tarea :
         solucion_fase_constructiva_.getSolucion().first[i]) {
      if (tarea != 0) std::cout << tarea << " | ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Método que genera una solución inicial a partir de la cual se van a
 * realizar búsquedas locales
 * @param maquina máquina en la que se va a reinsertar las tareas
 * @param problema
 * @return true en caso de que se encuentre una solución mejor
 * @return false en caso de que no se encuentre una solución mejor
 */
bool ReinsercionIntra::solucionEncontrada_(std::vector<int>& maquina,
                                           const Problema& problema) {
  int tct_maquina{calcularTCTMaquina(maquina, problema.getValoresArcos())};
  for (int i{1}; i < maquina.size(); ++i) {
    // Eliminamos la tarea
    int tarea{maquina[i]};
    maquina.erase(maquina.begin() + i);
    for (int j{1}; j < maquina.size(); ++j) {
      maquina.emplace(maquina.begin() + j, tarea);
      int tct{calcularTCTMaquina(maquina, problema.getValoresArcos())};
      if (tct < tct_maquina) return true;
      maquina.erase(maquina.begin() + j);
    }
    // no ha mejorado el tct, por lo que devolvemos la tarea a su posición
    // original
    maquina.emplace(maquina.begin() + i, tarea);
  }
  return false;
}

/**
 * @brief Método en el que se explora soluciones vecinas a partir de una
 * solución inicial obtenida
 * @param problema
 * @param numero_maximo_intentos número máximo de intentos que se van a realizar
 * para parar en caso de que no se encuentre una solución mejor
 * @return Solucion
 */
Solucion ReinsercionIntra::explorarVecindario(const Problema& problema,
                                              int numero_maximo_intentos) {
  // Primero encontramos una solución vecina inicial en alguna de las máquinas
  int maquina_mejorada;
  for (int i{0}; i < solucion_fase_constructiva_.getSolucion().first.size();
       ++i) {
    if (solucionEncontrada_(solucion_fase_constructiva_.getSolucion().first[i],
                            problema)) {
      maquina_mejorada = i;
      break;
    }
  }
  // A partir de la solución econtrada anteriormente seguimos buscando
  // soluciones
  int numero_intentos{0};
  for (int maquina{maquina_mejorada};
       maquina < solucion_fase_constructiva_.getSolucion().first.size();
       ++maquina) {
    while (numero_intentos < numero_maximo_intentos) {
      (solucionEncontrada_(solucion_fase_constructiva_[maquina], problema))
          ? numero_intentos = 0
          : ++numero_intentos;
    }
    numero_intentos = 0;
  }
  solucion_fase_constructiva_.setCosteTotal(calcularTCTTotalMaquinas(
      solucion_fase_constructiva_, problema.getValoresArcos()));
  return solucion_fase_constructiva_;
}