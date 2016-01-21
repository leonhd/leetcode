//#include "median.h"
#include "median_finder.h"
#include "palindromic.h"
#include "rational_decimal.h"
#include "integer_div.h"
#include "wildcard_match.h"
#include "decode_ways.h"
#include "text_justification.h"
#include <iostream>
#include <time.h>

void test_median_finder(int count)
{
	MedianFinder mf;
	srand(time(nullptr));
// 	std::vector<int> data = { 31147, 9382, 11090, 28135, 6667, 4840, 26015, 22019, 10736, 25295, 28269, 27732, 1545, 23963, 3080, 
// 		14279, 19491, 21042, 6349, 5142, 26783, 15557, 7228, 13966, 6180, 4529, 31311, 28693, 12689, 12195, 11530, 20587, 19510, 
// 		15616, 15444, 3760, 5699, 29828, 26629, 23335, 28544, 9513, 14400, 32313, 7231, 26954, 26627, 26813, 9360, 22792, 24060, 
// 		6518, 13235, 15341, 10143, 31709, 3027, 32207, 10869, 9249, 25073, 27383, 32695, 3181, 13854, 30595, 11803, 14185, 31725, 
// 		5641, 13806, 23555, 10024, 24957, 9059, 32367, 28866, 7765, 6955, 6764, 26637, 22250, 5445, 17098, 9261, 5922, 14872, 23081, 
// 		10701, 2892, 5567, 18691, 22800, 1611, 5540, 21741, 30666, 13047, 1104, 32025, 11249, 29888, 30593, 32, 31310, 15253, 25725, 
// 		28414, 7544, 20228, 20135, 29022, 18691};
	std::vector<int> data;
	data.reserve(count);
	for (int i = 0; i < count; ++i)
		data.push_back(rand());

	std::vector<double> median;
	median.reserve(data.size());

	int64_t t0, t1, freq;
	QueryPerformanceCounter((LARGE_INTEGER*)&t0);
	for (int i = 0; i < data.size(); ++i)
	{
		mf.addNum(data[i]);

		//if (i % 100 == 0)
		median.push_back(mf.findMedian());
	}
	QueryPerformanceCounter((LARGE_INTEGER*)&t1);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	fprintf(stdout, "finding median %d times costs %I64fms\n", count, ((t1 - t0) * 1000000 / freq) / 1000.0);
}

void test_rational_calc(int32_t num, int32_t denom)
{
	std::cout << num << " / " << denom << " == " << rational_decimal_calculator_t::calc(num, denom) << std::endl;
}
void test_int_div(int32_t divident, int32_t divisor)
{
	std::cout << divident << " / " << divisor << " == " << integer_div_t::calc(divident, divisor) << std::endl;
}

void test_str_wild_match(string src, string pat)
{
	const char *psrc = src.c_str();
	const char *ppat = pat.c_str();
	bool is_match = wildcard_matcher_t::match(psrc, psrc + src.length(), ppat, ppat + pat.length());
	std::cout << src << " match " << pat << " => " << is_match << std::endl;
}

void test_str_decode(string str)
{
	std::cout << str << " can be decoded in " << str_decode_counter_t::calc(str) << " ways\n";
}

void test_text_justify()
{
	vector<string> words;
	words.push_back("");
	words.push_back("This");
	words.push_back("is");
	words.push_back("a");
	words.push_back("example");
	words.push_back("of");
	words.push_back("text");
	words.push_back("justification");
	words.push_back("algorithm");
	vector<string> ret = text_justifier_t::exec(words, 30);
	for each (auto txt in ret)
	{
		std::cout << txt << std::endl;
	}
}
int main(int argc, char **argv)
{

	test_text_justify();
	return 0;

	test_str_decode("1787897759966261825913315262377298132516969578441236833255596967132573482281598412163216914566534565");
	test_str_decode("110");
	test_str_decode("7541387519572282368613553811323167125532172369624572591562685959575371877973171856836975137559677665");
	test_str_decode("1010");
	// 	test_str_wild_match("abclbcabbcca", "*ab*bcca*");
// 	test_str_wild_match("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");
// 	test_str_wild_match("aa", "a*");
// 	test_str_wild_match("ab", "?*");
// 	test_str_wild_match("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b");
// 	test_str_wild_match("a", "aa");
// 	test_str_wild_match("aa", "aa");
// 	test_str_wild_match("aaa", "aa");
// 	test_str_wild_match("aab", "c*a*b");
// 	test_str_wild_match("aab", "a*b");



	return 0;
	//test_median_finder(100000);
}