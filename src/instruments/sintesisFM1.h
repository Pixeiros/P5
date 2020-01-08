#ifndef SINTESISFM1
#define SINTESISFM1

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class SintesisFM1: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index, N, anterior, siguiente;
    unsigned int step, step1, step2, phase, vel, steps, pesos, indexs, indexss;
    unsigned int nota, note;
    unsigned int I, fm, fo, N1, N2; 
	  float A;
    std::vector<float> tbl;
  public:
    SintesisFM1(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif