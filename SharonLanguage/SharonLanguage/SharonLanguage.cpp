#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <cstdio>
#include <tchar.h>
#include <stack>
#include <cmath>
#include <fstream>
#include <locale>
#include <codecvt>


using namespace std;



namespace babo_language {
	map<wstring, int> vars;


	vector<wstring> split(wstring input, wchar_t dlim) {
		vector<wstring> result;

		wstring stringBuffer = L"";

		for (auto c : input) {
			if (c == dlim) {
				result.push_back(stringBuffer);
				stringBuffer.clear();
			}
			else
				stringBuffer.push_back(c);
		}

		if (stringBuffer.size()) result.push_back(stringBuffer);

		return result;
	}



	int merong_to_num(wstring str) {
		if (str[0] == L'바') {
			return vars[str];
		}
		if (str[0] == L'보') {
			wstring rev = L"";
			for (int i = str.size() - 1; i >= 0; --i)
				rev.push_back(str[i]);

			return -vars[rev];
		}

		int me_cnt = 0;
		wstring tmp = L"메롱";
		int rong_cnt = 0;

		if (str[0] == tmp[0]) {
			int i = 0;

			while (str[i] == tmp[0]) {
				me_cnt++;
				i++;
			}

			while (str.size() > i) {
				rong_cnt++;
				i++;
			}

			return pow(10, me_cnt - 1) * rong_cnt;
		}

		else {
			int i = 0;

			while (str[i] == tmp[1]) {
				rong_cnt++;
				i++;
			}

			while (str.size() > i) {
				me_cnt++;
				i++;
			}

			return (pow(10, me_cnt - 1) * rong_cnt) * (-1);
		}
	}



	vector<wstring> merong_split(wstring str) {
		vector<wstring> ret;
		wstring tmp = L"메롱";
		wstring cur = L"";

		for (int i = 0; i < str.size();) {
			if (str[i] == tmp[0]) {
				while (str[i] == tmp[0])
					cur.push_back(str[i++]);

				while (str.size() > i) {
					if (str[i] == tmp[1])
						cur.push_back(str[i++]);
					else
						break;
				}

				ret.push_back(cur);
				cur.clear();
			}

			else if (str[i] == tmp[1]) {
				while (str[i] == tmp[1])
					cur.push_back(str[i++]);

				while (str.size() > i) {
					if (str[i] == tmp[0])
						cur.push_back(str[i++]);
					else
						break;
				}

				ret.push_back(cur);
				cur.clear();
			}

			else if (str[i] == L'바') {
				while (str[i] == L'바')
					cur.push_back(str[i++]);

				while (str.size() > i) {
					if (str[i] == L'보')
						cur.push_back(str[i++]);
					else
						break;
				}

				ret.push_back(cur);
				cur.clear();
			}

			else {
				while (str[i] == L'보')
					cur.push_back(str[i++]);

				while (str.size() > i) {
					if (str[i] == L'바')
						cur.push_back(str[i++]);
					else
						break;
				}

				ret.push_back(cur);
				cur.clear();
			}
		}

		return ret;
	}



	void make_vars(wstring line) {
		wstring name = L"";
		int i = 0;

		while (line[i] != L'는') {
			name.push_back(line[i++]);
		}

		i++;

		int num = 0;
		auto arr = merong_split(line.substr(i));

		for (auto s : arr) {
			num += merong_to_num(s);
		}

		vars[name] = num;
	}





	void yackoruji_ggaggung_print(wstring line) {
		int i = 0;


		while (line[i] != L'꿍') ++i;
		++i;


		auto arr = split(line.substr(i), L',');

		for (auto s : arr) {
			auto mr = merong_split(s);
			int num = 0;

			for (auto m : mr) {
				num += merong_to_num(m);
			}

			cout << num;
		}
	}




	void yackoruji_ebebe_print(wstring line) {
		int i = 0;


		while (line[i] != L'벱') ++i;
		++i;


		auto arr = split(line.substr(i), L',');

		for (auto s : arr) {
			auto mr = merong_split(s);
			int num = 0;

			for (auto m : mr) {
				num += merong_to_num(m);
			}

			wcout << wchar_t(num);
		}
	}




	void read_line(wstring code) {
		vector<wstring> arr = split(code, L'\n');

		for (auto line : arr) {
			if (regex_match(line, wregex(L"[바]+[보]+는.*"))) {
				make_vars(line);
			}
			else if (regex_match(line, wregex(L"약오르지까꿍.*"))) {
				yackoruji_ggaggung_print(line);
			}
			else if (regex_match(line, wregex(L"약오르지에베벱.*"))) {
				yackoruji_ebebe_print(line);
			}
		}
	}
};




int main() {
	locale::global(locale(".UTF-8"));

	wifstream ifs("C:\\Users\\John\\Documents\\GitHub\\babo-language\\SharonLanguage\\test.txt");
	wstring code = L"";
	wstring line = L"";



	while (getline(ifs, line)) {
		code += line + L"\n";
	}


	babo_language::read_line(code);


	return 0;
}



/*

#my code

바보는메롱!
바바보는메메롱!
바바바보는메메롱롱롱메롱!
바바바바보는바보바보!
바바바바바바보는보바보바!


약오르지바보!
잡아봐라바보!

*/