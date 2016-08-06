#include <iostream>
#include <vector>
#include <random>

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <ctime>


using namespace std;


volatile bool stopped = false;


uint64_t next_rand (uint64_t x)
{
	x ^= (x << 12);
	x ^= (x >> 25);
	x ^= (x >> 27);
	return x * UINT64_C(2685821657736338717);
}


//void write_random (void *buffer, int buffer_size, FILE *outfile)
//{
//	uint64_t rand_state = next_rand((uint64_t)time(NULL));
//	size_t count = 0;
//	while ((count = fread(buffer, 1, buffer_size, outfile)) > 0) {
//		uint8_t *ptr = static_cast<uint8_t*>(buffer);
//		while (ptr < ((uint8_t *)buffer + buffer_size)) {
//			*(uint64_t *)ptr = rand_state;
//			rand_state = next_rand(rand_state);
//			ptr += sizeof(uint64_t);
//		}
//		fwrite()
//	}
//}


void write_random (void *buffer, int buffer_size, FILE *outfile)
{
	uint64_t rand_state = next_rand((uint64_t)time(NULL));
	while (!stopped) {
		uint8_t *ptr = static_cast<uint8_t*>(buffer);
		while (ptr < ((uint8_t *)buffer + buffer_size)) {
			*(uint64_t *)ptr = rand_state;
			rand_state = next_rand(rand_state);
			ptr += sizeof(uint64_t);
		}
		fwrite(buffer, 1, buffer_size, outfile);
	}
}


int main (int argc, char *argv[])
{
	int buffer_size = 16 * 1024;
	vector<uint8_t> buffer(buffer_size);
	FILE *outfile = stdout;
	write_random((void*)&buffer[0], buffer_size, outfile);
}
