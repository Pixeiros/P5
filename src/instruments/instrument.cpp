#include <iostream>
#include "instrument_dumb.h"
#include "seno.h"
#include "SintesisFM1.h"
#include "instrumentFM.h"

/*
  For each new instrument:
  - Add the header in this file
  - Add the call to the constructor in get_instrument() (also in this file)
  - Add the source file to src/meson.build
*/

using namespace std;

namespace upc {
  Instrument * get_instrument(const string &name,
			      const string &parameters) {
    Instrument * pInst = 0;
    //    cout << name << ": " << parameters << endl;
    if (name == "InstrumentDumb") {
      pInst = (Instrument *) new InstrumentDumb(parameters);
    }
    if (name == "Seno") {
      pInst = (Instrument *) new Seno(parameters);
    }
    if (name == "SintesisFM1") {
      pInst = (Instrument *) new SintesisFM1(parameters);
    }
    if (name == "InstrumentFM") {
      pInst = (Instrument *) new InstrumentFM(parameters);
    }
    return pInst;
  }
}
