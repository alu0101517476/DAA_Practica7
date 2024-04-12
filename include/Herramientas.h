#pragma once

#include <iostream>
#include <vector>

#include "Solucion.h"

struct TernaTctGrasp {
  int tct_;
  int maquina_;
  int posicion_;
};

int calcularTCTMaquina(const std::vector<int>& maquina, const std::vector<std::vector<int>>& valores_arcos);

int calcularTCTOptimo(int maquina, int posicion, int tarea, Solucion& solucion_algoritmo, const std::vector<std::vector<int>>& valores_arcos);

int calcularTCTTotalMaquinas(Solucion& solucion_algoritmo, const std::vector<std::vector<int>>& valores_arcos);

int calcularTCTTotalMaquinas(std::vector<std::vector<int>>& matriz_solucion, const std::vector<std::vector<int>>& valores_arcos);

int elegirEstructuraEntornoGrasp();

void ayuda();