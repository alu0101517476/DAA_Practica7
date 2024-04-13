#include "../include/Algoritmos_vecindario/ReinsercionEntre.h"

void ReinsercionEntre::imprimirSolucion() {
  std::cout << solucion_fase_constructiva_.getSolucion().second << std::endl;
  for (int i{0}; i < solucion_fase_constructiva_.getSolucion().first.size(); ++i) {
    std::cout << i << ": ";
    for (const auto& tarea : solucion_fase_constructiva_.getSolucion().first[i]) {
      if (tarea != 0) std::cout << tarea << " | ";
    }
    std::cout << std::endl;
  }
}

bool ReinsercionEntre::solucionEncontrada_(
    std::vector<int>& maquina1, std::vector<int>& maquina2,
    const std::vector<std::vector<int>>& valores_arcos) {
  int tct_total{
      calcularTCTTotalMaquinas(solucion_fase_constructiva_, valores_arcos)};
  for (int i{1}; i < maquina1.size(); ++i) {
    // Eliminamos la tarea
    int tarea{maquina1[i]};
    maquina1.erase(maquina1.begin() + i);
    for (int j{1}; j < maquina2.size(); ++j) {
      maquina2.emplace(maquina2.begin() + j, tarea);
      int tct{
          calcularTCTTotalMaquinas(solucion_fase_constructiva_, valores_arcos)};
      if (tct < tct_total) return true;
      maquina2.erase(maquina2.begin() + j);
    }
    // Devolvemos la tarea a su posición original
    maquina1.emplace(maquina1.begin() + i, tarea);
  }
  return false;
}

Solucion ReinsercionEntre::explorarVecindario(
    const std::vector<std::vector<int>>& valores_arcos,
    int numero_maximo_intentos) {
  int maquina_mejorada;
  size_t size_solucion{solucion_fase_constructiva_.getSolucion().first.size()};
  for (int i{0}; i < size_solucion; ++i) {
    for (int j{0}; j < size_solucion; ++j) {
      if (j != i) {
        if (solucionEncontrada_(
                solucion_fase_constructiva_.getSolucion().first[i],
                solucion_fase_constructiva_.getSolucion().first[j],
                valores_arcos)) {
          maquina_mejorada = i;
          break;
        }
      }
    }
  }
  // A partir de la solución encontrada anteriormente, seguimos buscando
  // soluciones
  int numero_intentos{0};
  for (int maquina{maquina_mejorada}; maquina < size_solucion; ++maquina) {
    for (int k{0}; k < size_solucion; ++k) {
      while (numero_intentos < numero_maximo_intentos) {
        (solucionEncontrada_(
            solucion_fase_constructiva_.getSolucion().first[maquina],
            solucion_fase_constructiva_.getSolucion().first[k], valores_arcos))
            ? numero_intentos = 0
            : ++numero_intentos;
      }
      numero_intentos = 0;
    }
  }
  solucion_fase_constructiva_.setCosteTotal(
      calcularTCTTotalMaquinas(solucion_fase_constructiva_, valores_arcos));
  return solucion_fase_constructiva_;
}