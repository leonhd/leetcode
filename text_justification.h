#pragma once
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;

class text_justifier_t
{
public:
	static vector<string> exec(vector<string> & words, int32_t max_width)
	{
		vector<char> str_builder;
		str_builder.reserve(2 * max_width);
		vector<string> ret;

		if (max_width == 0)
		{
			if (words.size() == 1 && words[0].length() == 0)
				ret.push_back("");
			return ret;
		}
		
		for (int32_t i = 0; i < words.size();)
		{
			int32_t len = 0;
			int32_t cur = i;
			while (cur < words.size() && len < max_width)
				len += words[cur++].length();

			if (len > max_width)
			{
				--cur;
				len -= words[cur].length();
			}

			while (len + cur - i - 1 > max_width)
			{
				--cur;
				len -= words[cur].length();
			}

			int32_t spaces = cur - i - 1;
			str_builder.resize(max_width + 1);
			if (len == 0)
			{
				for (int32_t c = 0; c < max_width; ++c)
					str_builder[c] = ' ';
			}
			else if (spaces == 0)
			{
				std::copy(words[i].begin(), words[i].end(), str_builder.begin());
				for (int32_t c = words[i].length(); c < max_width; ++c)
					str_builder[c] = ' ';
			}
			else if (cur == words.size())
			{
				auto ite = str_builder.begin();
				
				std::copy(words[i].begin(), words[i].end(), ite);
				ite += words[i].length();
				
				int32_t j = i + 1;
				for (; j < cur; ++j)
				{
					*(ite++) = ' ';
					std::copy(words[j].begin(), words[j].end(), ite);
					ite += words[j].length();
				}

				while (ite < str_builder.end())
				{
					*(ite++) = ' ';
				}
			}
			else if (spaces == 1)
			{
				int32_t blanks = max_width - len;
				std::copy(words[i].begin(), words[i].end(), str_builder.begin());

				int32_t blank_beg = words[i].length(), blank_end = blank_beg + blanks;
				for (int32_t c = blank_beg; c < blank_end; ++c)
					str_builder[c] = ' ';

				std::copy(words[i + 1].begin(), words[i + 1].end(), str_builder.begin() + blank_end);
			}
			else
			{
				int32_t blanks = max_width - len;
				int32_t blank_len = 0, rh_blanks = 0, lh_blanks = 0;
				if (blanks % spaces != 0)
				{
					double avg_blanks = blanks / (double)spaces;
					blank_len = avg_blanks;
					rh_blanks = (blank_len + 1) * spaces - blanks;
					lh_blanks = spaces - rh_blanks;
				}
				else
				{
					blank_len = blanks / spaces - 1;
					lh_blanks = spaces;
					rh_blanks = 0;
				}

				auto ite = str_builder.begin();
				std::copy(words[i].begin(), words[i].end(), ite);
				ite += words[i].length();
				int32_t j = i + 1;
				for (; j < cur - rh_blanks; ++j)
				{
					for (int32_t c = 0; c <= blank_len; ++c)
						*(ite++) = ' ';

					std::copy(words[j].begin(), words[j].end(), ite);
					ite += words[j].length();
				}
				for (; j < cur; ++j)
				{
					for (int32_t c = 0; c < blank_len; ++c)
						*(ite++) = ' ';

					std::copy(words[j].begin(), words[j].end(), ite);
					ite += words[j].length();
				}
			}
			str_builder[max_width] = '\0';

			ret.push_back(&str_builder[0]);
			str_builder.clear();

			i = cur;
		}

		return ret;
	}
};

#if 0
class Solution {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		return text_justifier_t::exec(words, maxWidth);
	}
};
#endif
