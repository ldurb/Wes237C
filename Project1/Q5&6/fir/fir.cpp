/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"
// #include "ap_int.h"
void fir (
  data_t *y,
  data_t x
  )
{

	custom_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	// coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

	// Write your code here
	static
		data_t shift_reg[N];
		custom_t acc;
		int i;

	acc = 0;
	#pragma HLS array_partition variable=shift_reg complete dim=1
	#pragma HLS array_partition variable=c complete dim=1

	Shift_Reg_Loop:
	for(i = N - 1; i > 1; i = i-2){
		shift_reg[i] = shift_reg[i - 1];
		shift_reg[i-1] = shift_reg[i - 2];
	}
	if(i==1){
		shift_reg[1]= shift_reg[0];
	}
	shift_reg[0] = x;


	Shift_Accum_Loop:
	for (i = N - 1; i >= 3; i-=4){
		acc += shift_reg[i] * c[i] + shift_reg[i-1] * c[i-1] + shift_reg[i-2] * c[i-2] + shift_reg[i-3] * c[i-3];
	}

	for(; i>=0 ; i--){
		acc += shift_reg[i] * c[i];
		// shift_reg[i] = x;
	}
	*y = acc;
}

