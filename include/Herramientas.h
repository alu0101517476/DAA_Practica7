#pragma once

#include <iostream>
#include <vector>

#include "Solucion.h"

int calcularTCTMaquina(const std::vector<int>& maquina, const std::vector<std::vector<int>>& valores_arcos);

int calcularTCTOptimo(int maquina, int posicion, int tarea, Solucion& solucion_algoritmo, const std::vector<std::vector<int>>& valores_arcos);

void ayuda();