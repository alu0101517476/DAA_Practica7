#pragma once

#include <iostream>

#include "Solucion.h"

class Algoritmo {
 public:
  virtual Solucion resolver() = 0;
};