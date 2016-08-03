#pragma once

#include <vector>
#include <functional>
#include <algorithm>

#include <cmath>


template <typename FI, typename FP = double>
void fillWithSines (const FI& begin, const FI& end, const FP step = 1.0)
{
	const std::vector<std::function<FP(FP)>> functions = {
		[] (FP x) -> FP { return sin(x); },
		[] (FP x) -> FP { return sin(2 * x); },
		[] (FP x) -> FP { return sin(4 * x); },
		[] (FP x) -> FP { return sin(8 * x); },
		[] (FP x) -> FP { return sin(16 * x); }
	};
	FP x = 0;
	for (FI i = begin; i != end; ++i) {
		FP y = 0.0;
		for (auto& fn : functions) {
			y += fn(x);
		}
		*i = y;
		x += step;
	}
}

