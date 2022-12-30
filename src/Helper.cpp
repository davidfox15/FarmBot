#include "Helper.h"

int getDif(int a, int b) {
	int dif = a - b;
	if (dif < 0) dif = dif * -1;
	return dif;
}