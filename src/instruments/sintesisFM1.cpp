#include <iostream>
#include <math.h>
#include "sintesisFM1.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

SintesisFM1::SintesisFM1(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  
  //  You can use the class keyvalue to parse "param" and configure your instrument.
  //  Take a Look at keyvalue.h    

  if (!kv.to_int("N",N))
    N = 40; //default value
    
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  for (int i=0; i < N ; ++i) {
      tbl[i] = sin(phase);
      phase += step;
  }

}


void SintesisFM1::command(long cmd, long note, long vel) {
  if (cmd == 9) {
  bActive = true;
  adsr.start();
  step = 0;
  index = 0;
  indexs = 0;
  steps = 0;
  I=0.5; 
  N=100;
  N1=100;
  N2=20;
  float f0=440.0*pow(2,(((float)note-69.0)/12.0));
  nota=f0/SamplingRate;
  A=vel/127.;
  fm=N2*f0/N1;
  step1=nota*N1;
  step2=nota*N2;

  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & SintesisFM1::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

 for (unsigned int i=0; i < x.size() ; ++i) { 
  indexs += step1;
  indexss += step2;
  if(indexs>=tbl.size()){
    indexs = indexs - tbl.size(); 
  }
    if(indexss>=tbl.size()){
    indexss = indexss - tbl.size(); 
  }
  anterior = (int)indexs;
  pesos = indexs-anterior;
  if(anterior==tbl.size()-1){
    siguiente=0;
  }
  else siguiente = anterior+1;
    x[i] = pesos*A*tbl[anterior+I*tbl[indexss]]+(1-pesos)*A*tbl[siguiente+I*tbl[indexss]];  
  }

  adsr(x);

  return x;
}
