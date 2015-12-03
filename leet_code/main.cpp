#include "median.h"
#include "median_finder.h"
#include <iostream>
#include <time.h>

void test_median_finder(int count)
{
	MedianFinder mf;
	srand(time(nullptr));
	std::vector<int> data;
	data.reserve(count);
	std::vector<double> median;
	median.reserve(count);
	for (int i = 0; i < count; ++i)
		data.push_back(rand());

	int64_t t0, t1, freq;
	QueryPerformanceCounter((LARGE_INTEGER*)&t0);
	for (int i = 0; i < count; ++i)
	{
		mf.addNum(data[i]);
		median.push_back(mf.findMedian());
	}
	QueryPerformanceCounter((LARGE_INTEGER*)&t1);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	fprintf(stdout, "finding median %d times costs %dms\n", count, (t1 - t0) * 1000 / freq);
}
int main(int argc, char **argv)
{
	test_median_finder(100000);
}