#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <unistd.h>
#include <csignal>

using namespace std;

vector<uint64_t> v(1 << 16);

void end()
{
	uint64_t sum = 0;
	for (const uint64_t& n : v)
		sum += n;
	printf("n: %lu\n", sum);
}

void handle_sigterm (int signo)
{
	printf("ending prematurely\n");
	end();
	exit(0);
}

int main (int argc, char *argv[])
{
	if (signal(SIGINT, handle_sigterm) == SIG_ERR) {
		printf("ERROR: unable to set handler for SIGINT\n");
		return EXIT_FAILURE;
	}

	for (uint64_t k = 0; k < numeric_limits<uint64_t>::max(); ++k) {
		for (uint64_t i = 0; i < v.size(); ++i) {
			v[i] = i ^ k;
		}
	}

	end();

	return 0;
}
