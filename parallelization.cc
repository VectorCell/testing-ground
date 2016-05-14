
#include "parallelization.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <cstdint>


using namespace std;

void ranged_sums ()
{
	size_t size = 1 << 10;

	vector<int> nums(size);
	
	// fill
	printf("filling nums ...\n");
	#pragma omp parallel for
	for (int i = 0; i < (int)size; ++i) {
		nums[i] = rand() % 1000;
	}

	// all possibilities
	size_t bytes_generated = 0;
	printf("calculating all possible sublist sums ...\n");
	for (int x = 0; x < (int)size; ++x) {
		#pragma omp parallel for
		for (int y = x; y < (int)size; ++y) {
			accumulate(&nums[x], &nums[y], 0);
			bytes_generated += sizeof(int64_t);
		}
	}

	printf("generated %ld bytes\n", bytes_generated);
}

int main (int argc, char *argv[])
{
	ranged_sums();

	return 0;
}
