#include "histogram.h"
std::ostream& operator << (std::ostream& O, const Histogram& d)
{
   for(int i=0; i<d.size(); i++)
       O << d[i].frequency << " Hz  <->  " << d[i].amplitude << " dB" << std::endl;
   return O;
}
