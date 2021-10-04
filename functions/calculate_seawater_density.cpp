#include <admodel.h>

using namespace std;

void calculate_seawater_density(dvar_vector& density , dvar_vector temp , dvar_vector sal, dvar_vector depth){

  int bottom(temp.size());

	  double a0(999.842594);
	  double a1(6.793953e-2);
	  double a2(-9.095290e-3);
	  double a3(1.001685e-4);
	  double a4(-1.120083e-6);
	  double a5(6.536332e-9);
	  double b0(8.2449e-1);
	  double b1(-4.0899e-3);
	  double b2(7.6438e-5);
	  double b3(-8.2467e-7);
	  double b4(5.3875e-9);
	  double c0(-5.7246e-3);
	  double c1(1.0227e-4);
	  double c2(-1.6546e-6);
	  double d0(4.8314e-4);
	  double e0(19652.21);
	  double e1(148.420600);
	  double e2(-2.327105);
	  double e3(1.360477e-2);
	  double e4(-5.155288e-5);
	  double f0(54.674600);
	  double f1(-0.603459);
	  double f2(1.099870e-2);
	  double f3(-6.167000e-5);
	  double g0(7.944e-2);
	  double g1(1.6483e-2);
	  double g2(-5.3009e-4);
	  double h0(3.2399);
	  double h1(1.43713e-3);
	  double h2(1.16092e-4);
	  double h3(-5.77905e-7);
	  double i0(2.2838e-3);
	  double i1(-1.0981e-5);
	  double i2(-1.6078e-6);
	  double j0(1.91075e-4);
	  double k0(8.50935e-5);
	  double k1(-6.12293e-6);
	  double k2(5.27870e-8);
	  double m0(-9.9348e-7);
	  double m1(2.0816e-8);
	  double m2(9.1697e-10);

	  dvariable p(0);
	  for (int z =1 ; z<=bottom; z++){
          // calculate pressure (bar) at depth z:
	  //
	  p = depth[z]/10;

	dvariable rho_SMOW = a0 + a1*temp[z] + a2*pow(temp[z],2) + a3*pow(temp[z],3) + a4*pow(temp[z],4) + a5*pow(temp[z],5);
	dvariable B1 = b0 + b1*temp[z] + b2*pow(temp[z],2) + b3*pow(temp[z],3) + b4*pow(temp[z],4);
	dvariable C1 = c0 + c1*temp[z] + c2*pow(temp[z],2);
	dvariable rho = rho_SMOW + B1*sal[z] + C1*pow(sal[z],1.5) + d0*pow(sal[z],2);

	dvariable Kw = e0 + e1*temp[z] + e2*pow(temp[z],2) + e3*pow(temp[z],3) + e4*pow(temp[z],4);
	dvariable F1 = f0 + f1*temp[z] + f2*pow(temp[z],2) + f3*pow(temp[z],3);
	dvariable G1 = g0 + g1*temp[z] + g2*pow(temp[z],2);

	dvariable K0 = Kw + F1*sal[z] + G1*pow(sal[z],1.5);
        
	dvariable Aw = h0 + h1*temp[z] + h2*pow(temp[z],2) + h3*pow(temp[z],3);
	dvariable A1 = Aw + (i0 + i1*temp[z] + i2*pow(temp[z],2))*sal[z] + j0*pow(sal[z],1.5);
	dvariable Bw = k0 + k1*temp[z] + k2*pow(temp[z],2);
	dvariable B2 = Bw +(m0 + m1*temp[z]+m2*pow(temp[z],2)) * sal[z];

	dvariable K = K0 + A1*p + B2*pow(p,2);
	density[z] = rho/(1 - p/K) - 1000;
  }

}
