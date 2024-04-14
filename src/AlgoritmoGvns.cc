#include "../include/AlgoritmoGvns.h"

int AlgoritmoGvns::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

Solucion AlgoritmoGvns::perturbacionAleatoria(const Solucion& solucion) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribucion(1, 4);
  int movimiento = distribucion(gen);

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

Solucion AlgoritmoGvns::perturbacion(const Solucion& solucion) {
  ReinsercionEntre reinsercion_entre{solucion};
  return reinsercion_entre.explorarVecindario(problema_.getValoresArcos(), 10);
}

Solucion AlgoritmoGvns::VND(const Solucion& solucion) {
  solucion_algoritmo_ = solucion;
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
        Solucion solucion_actual{intercambio_intra.explorarVecindario(problema_, 10)};
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
        Solucion solucion_actual{reinsercion_intra.explorarVecindario(problema_, 10)};
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
        Solucion solucion_actual{intercambio_entre.explorarVecindario(problema_.getValoresArcos(), 10)};
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
      Solucion solucion_perturbada{perturbacion(solucion_actual)};
      // (b) Local search by VND
      Solucion solucion_vnd{VND(solucion_perturbada)};
      // (c) move or not
      if (calcularTCTTotalMaquinas(solucion_actual,
                                   problema_.getValoresArcos()) <
          calcularTCTTotalMaquinas(solucion_vnd, problema_.getValoresArcos())) {
        solucion_actual = solucion_vnd;
        solucion_actual.setCosteTotal(calcularTCTTotalMaquinas(solucion_actual,
                                                               problema_.getValoresArcos()));
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
      Solucion solucion_perturbada{perturbacion(solucion_actual)};
      // (b) Local search by VND
      Solucion solucion_vnd{VND(solucion_perturbada)};
      // (c)move or not
      if (calcularTCTTotalMaquinas(solucion_actual,
                                   problema_.getValoresArcos()) <
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
