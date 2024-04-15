#include "../include/AlgoritmoGvns.h"

/**
 * @brief Método que calcula el TCT total de todas las máquinas, a partir del
 * atributo "solucion_algoritmo_"
 * @return int el TCT total
 */
int AlgoritmoGvns::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

/**
 * @brief Método que realiza las perturbaciones que son necesarias en el
 * algoritmo GVNS pero escogiendo una exploración de vecindario aleatoria entre
 * las cuatro posibles. Esto se realiza por si queremos que nos de un conjunto
 * de soluciones más variada y en algun posible caso, que podamos salir de un
 * óptimo local
 * @param solucion solución que tenemos en ese momento y que queremos perturbar
 * @return Solucion solución después de haber sido perturbada
 */
Solucion AlgoritmoGvns::perturbacionAleatoria_(const Solucion& solucion) {
  // Escogemos un número aleatorio entre 1 y 4
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribucion(1, 4);
  int movimiento = distribucion(gen);
  // Realizamos la perturbación dado el número aleatorio
  switch (movimiento) {
    case 1: {
      ReinsercionEntre reinsercion_entre{solucion};
      return reinsercion_entre.explorarVecindario(problema_.getValoresArcos(),
                                                  10);
    }

    case 2: {
      IntercambioIntra intercambio_intra{solucion};
      return intercambio_intra.explorarVecindario(problema_, 10);
    }

    case 3: {
      ReinsercionIntra reinsercion_intra{solucion};
      return reinsercion_intra.explorarVecindario(problema_, 10);
    }

    case 4: {
      IntercambioEntre intercambio_entre{solucion};
      return intercambio_entre.explorarVecindario(problema_.getValoresArcos(),
                                                  10);
    }

    default:
      std::cerr << "Error en la perturbación" << std::endl;
      exit(1);
  }
}

/**
 * @brief Método que realiza la perturbación de la solución que se le pasa como
 * argumento al método, en este caso la perturbación es la de Reinserción de
 * tareas entre máquinas
 * @param solucion solución que tenemos de la ejecución del algoritmo en ese
 * momento
 * @return Solucion solución después de haber sido perturbada
 */
Solucion AlgoritmoGvns::perturbacion_(const Solucion& solucion) {
  ReinsercionEntre reinsercion_entre{solucion};
  return reinsercion_entre.explorarVecindario(problema_.getValoresArcos(), 10);
}

/**
 * @brief Método que realiza el algoritmo de Búsqueda Local Variable (VND) para
 * la solución que se le pasa como argumento, este algoritmo es necesario para
 * la correcta ejecución del algoritmo GVNS
 * @param solucion solución que hemos obtenido hasta ese instante
 * @return Solucion solución después de haber sido modificada por el VND
 */
Solucion AlgoritmoGvns::VND_(const Solucion& solucion) {
  solucion_algoritmo_ = solucion;
  // Establecemos la l que indica el número de vecindarios
  int l{1};
  while (l <= 4) {
    switch (l) {
      case 1: {
        ReinsercionEntre reinsercion_entre{solucion_algoritmo_};
        Solucion solucion_actual{reinsercion_entre.explorarVecindario(
            problema_.getValoresArcos(), 10)};
        if (calcularTCTTotal() <
            calcularTCTTotalMaquinas(solucion_actual,
                                     problema_.getValoresArcos())) {
          solucion_algoritmo_ = solucion_actual;
          l = 1;
        } else {
          ++l;
        }
        break;
      }

      case 2: {
        IntercambioIntra intercambio_intra{solucion_algoritmo_};
        Solucion solucion_actual{
            intercambio_intra.explorarVecindario(problema_, 10)};
        if (calcularTCTTotal() <
            calcularTCTTotalMaquinas(solucion_actual,
                                     problema_.getValoresArcos())) {
          solucion_algoritmo_ = solucion_actual;
          l = 1;
        } else {
          ++l;
        }
        break;
      }

      case 3: {
        ReinsercionIntra reinsercion_intra{solucion_algoritmo_};
        Solucion solucion_actual{
            reinsercion_intra.explorarVecindario(problema_, 10)};
        if (calcularTCTTotal() <
            calcularTCTTotalMaquinas(solucion_actual,
                                     problema_.getValoresArcos())) {
          solucion_algoritmo_ = solucion_actual;
          l = 1;
        } else {
          ++l;
        }
        break;
      }

      case 4: {
        IntercambioEntre intercambio_entre{solucion_algoritmo_};
        Solucion solucion_actual{intercambio_entre.explorarVecindario(
            problema_.getValoresArcos(), 10)};
        if (calcularTCTTotal() <
            calcularTCTTotalMaquinas(solucion_actual,
                                     problema_.getValoresArcos())) {
          solucion_algoritmo_ = solucion_actual;
          l = 1;
        } else {
          ++l;
        }
        break;
      }

      default:
        std::cerr << "Error en el VND " << std::endl;
        break;
    }
  }
  return solucion_algoritmo_;
}

/**
 * @brief Método que ejecuta el algoritmo GVNS para dar una solución al problema
 * @return Solucion solución encontrada después de ejecutar el algoritmo
 */
Solucion AlgoritmoGvns::resolver() {
  // Obtenemos una solución inicial
  AlgoritmoGrasp grasp{problema_.getNombreFichero()};
  Solucion solucion_actual{grasp.faseConstructiva()};
  for (int i{0}; i < maximo_iteraciones_; ++i) {
    // Set k <- 1
    int k{1};
    // Repeat until k = kmax:
    do {
      // (a) Shaking
      Solucion solucion_perturbada{perturbacion_(solucion_actual)};
      // (b) Local search by VND
      Solucion solucion_vnd{VND_(solucion_perturbada)};
      // (c) move or not
      if (calcularTCTTotalMaquinas(solucion_actual,
                                   problema_.getValoresArcos()) >
          calcularTCTTotalMaquinas(solucion_vnd, problema_.getValoresArcos())) {
        solucion_actual = solucion_vnd;
        solucion_actual.setCosteTotal(calcularTCTTotalMaquinas(
            solucion_actual, problema_.getValoresArcos()));
        k = 1;
      } else {
        ++k;
      }
    } while (k <= 4);
  }
  solucion_algoritmo_ = solucion_actual;
  solucion_algoritmo_.setCosteTotal(calcularTCTTotal());
  return solucion_algoritmo_;
}

/**
 * @brief Método que ejecuta el algoritmo GVNS con la técnica de MultiArranque
 * para dar una solución al problema
 * @return Solucion solución encontrada después de ejecutar el algoritmo
 */
Solucion AlgoritmoGvns::resolverMultiArranque() {
  Solucion solucion_actual;
  AlgoritmoGrasp grasp{problema_.getNombreFichero()};
  for (int i{0}; i < maximo_iteraciones_; ++i) {
    // Obtenemos una solución inicial
    solucion_actual = grasp.faseConstructiva();
    // Set k <- 1
    int k{1};
    // Repeat until k = kmax:
    do {
      // (a) Shaking
      Solucion solucion_perturbada{perturbacion_(solucion_actual)};
      // (b) Local search by VND
      Solucion solucion_vnd{VND_(solucion_perturbada)};
      // (c)move or not
      if (calcularTCTTotalMaquinas(solucion_actual,
                                   problema_.getValoresArcos()) >
          calcularTCTTotalMaquinas(solucion_vnd, problema_.getValoresArcos())) {
        solucion_actual = solucion_vnd;
        k = 1;
      } else {
        ++k;
      }
    } while (k <= 4);
  }
  solucion_algoritmo_ = solucion_actual;
  return solucion_algoritmo_;
}
