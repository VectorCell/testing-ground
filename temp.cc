#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdint>

#include <unistd.h>

using namespace std;

const size_t BLOCKSIZE = 4 * 1024;

bool valid_char(char ch)
{
	if (ch == '\0')
		return true;
	else if (ch == '\t')
		return true;
	else if (ch == '\n')
		return true;
	else if (ch >= ' ' && ch <= '~')
		return true;
	else
		return false;
}

size_t process(const vector<uint8_t>& in, vector<uint8_t>& out, const size_t& count)
{
	out.resize(0);
	for (size_t k = 0; k < count; ++k) {
		if (valid_char(in[k])) {
			out.push_back(in[k]);
		}
	}
	return count - out.size();
}

size_t sanitize(FILE *infile, FILE *outfile)
{
	if (infile == NULL || outfile == NULL)
		return 0;

	vector<uint8_t> bufin(BLOCKSIZE);
	vector<uint8_t> bufout(BLOCKSIZE);

	size_t removed = 0;
	size_t count = 0;
	while ((count = fread(&bufin[0], 1, BLOCKSIZE, infile)) > 0) {
		removed += process(bufin, bufout, count);
		fwrite(&bufout[0], bufout.size(), 1, outfile);
	}
	return removed;
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

	size_t removed = sanitize(stdin, outfile);
	fprintf(stderr, "removed %zu bytes\n", removed);

	return EXIT_SUCCESS;
}
