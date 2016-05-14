#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdint>

#include <unistd.h>

using namespace std;

const int BLOCKSIZE = 4096;

bool blk_zeroed (void *block)
{
	uint8_t *ptr = static_cast<uint8_t*>(block);
	for (int k = 0; k < BLOCKSIZE; ++k) {
		if (ptr[k] != 0) {
			return false;
		}
	}
	return true;
}

size_t output_sparse(FILE *infile, FILE *outfile, size_t& n_skipped_blocks)
{
	if (infile == NULL || outfile == NULL)
		return 0;

	n_skipped_blocks = 0;

	vector<uint8_t> buffer(BLOCKSIZE);
	void *buf = &buffer[0];
	size_t total_bytes = 0;
	size_t count = 0;
	while ((count = fread(buf, 1, BLOCKSIZE, infile)) > 0) {
		total_bytes += count;
		if (blk_zeroed(buf)) {
			++n_skipped_blocks;
			fseek(outfile, count, SEEK_CUR);
		} else {
			fwrite(buf, count, 1, outfile);
		}
	}
	return total_bytes;
}

int main (int argc, char *argv[])
{
	FILE *outfile;
	string filename;
	if (argc >= 2) {
 		filename = argv[1];
 		outfile = fopen(filename.c_str(), "wb");
	} else {
		filename = "stdout";
		outfile = stdout;
	}

	if (outfile == NULL) {
		fprintf(stderr, "ERROR: unable to open file %s\n", filename.c_str());
		return EXIT_FAILURE;
	}

	size_t n_skipped_blocks = 0;
	size_t total_bytes = output_sparse(stdin, outfile, n_skipped_blocks);
	
	if (outfile != stdout) {
		if (0 != ftruncate(fileno(outfile), total_bytes)) {
			fprintf(stderr, "ERROR: unable to truncate file %s\n", filename.c_str());
		}
		fclose(outfile);
	}

	cout << "processed " << total_bytes << " bytes" << endl;
	cout << "skipped " << n_skipped_blocks << " data blocks" << endl;

	return EXIT_SUCCESS;
}
