#pragma once

#include <string>
#include <sstream>

#include <cmath>

template <typename T>
std::string ntos (const T& n)
{
	return static_cast<std::ostringstream*>(&(std::ostringstream() << n))->str();
}

template <typename T>
std::string bytestosize (const T& n, bool base2 = true)
{
	static const char labels[][4] 
		= {"B", "kiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"};
	T major = n;
	T minor = 0;
	int label_index = 0;
	for (int k = 0; k < sizeof(labels) / sizeof(labels[0]); ++k) {
		if (major < (base2 ? 1024 : 1000)) {
			label_index = k;
			break;
		} else {
			minor = major % (base2 ? 1024 : 1000);
			major /= (base2 ? 1024 : 1000);
		}
	}
	double minord = minor / static_cast<double>(base2 ? 1024 : 1000);
	std::string str
		= ntos(major)
		+ ntos(round(10 * minord) / 10).substr(1)
		+ " "
		+ std::string(labels[label_index]);
	return str;
	//return ntos(major) + " " + std::string(labels[label_index]) + " " + ntos(minor) + " " + std::string(labels[label_index - 1]);
}

