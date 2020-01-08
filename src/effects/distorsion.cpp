#include <iostream>
#include <math.h>
#include "distorsion.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

static float SamplingRate = 44100;

Distorsion::Distorsion(const std::string &param) {
  fase = 0;

  KeyValue kv(param);

  if (!kv.to_float("A", A))
    A = 0.5; //default value

  if (!kv.to_float("fm", fm))
    fm = 10; //default value

  inc_fase = 2 * M_PI * fm / SamplingRate;
}

void Distorsion::command(unsigned int comm) {
  if (comm == 1) fase = 0;
}

void Distorsion::operator()(std::vector<float> &x){
  for (unsigned int i = 0; i < x.size(); i++) {
    x[i] *= (1 - A) + A * sin(fase);
    fase += inc_fase;

    while(fase > 2 * M_PI) fase -= 2 * M_PI;
  }
}
