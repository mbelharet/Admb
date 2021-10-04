#include <admodel.h>
using namespace std;
void calculate_day_length(double& DL, double Time, double Lat, double const p){
    double theta = 0.2163108 + 2 * atan(0.9671396 * tan(0.00860 * (Time + 1 - 186)));
    double phi = asin(0.39795 * cos(theta));
    double aDL = (sin(p * PI / 180.) + sin(Lat * PI / 180.) * sin(phi)) / (cos(Lat * PI / 180.) * cos(phi));
   if(aDL>1.0){
     aDL = 1.0;
   }else if(aDL<-1.0){
     aDL = -1.0;
   }

   DL = 1.0 - (1.0 / PI) * acos(aDL);
   if(DL<1./24.){
      DL = 1./24.;
    }

}
