#include "../include/Algoritmos_vecindario/IntercambioIntra.h"

bool IntercambioIntra::solucionEncontrada_(std::vector<int>& maquina,
                                           const Problema& problema) {
  int tct_maquina{calcularTCTMaquina(maquina, problema.getValoresArcos())};
  for (int i{1}; i < maquina.size(); ++i) {
    for (int j{1}; j < maquina.size(); ++j) {
      if (i != j) {
        std::swap(maquina[i], maquina[j]);
        int tct{calcularTCTMaquina(maquina, problema.getValoresArcos())};
        if (tct < tct_maquina) return true;
        std::swap(maquina[j], maquina[i]);
      }
    }
  }
  return false;
}

Solucion IntercambioIntra::explorarVecindario(const Problema& problema,
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