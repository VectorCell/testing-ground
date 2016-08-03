#include "fft.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main (int argv, char *argc[])
{
	vector<double> vals(1000);

	fillWithSines(vals.begin(), vals.end(), 0.01);

	for (unsigned int k = 0; k < vals.size(); ++k) {
		cout << k << "\t" << vals[k] << "\t";

		

		cout << endl;
	}

	return 0;
}
