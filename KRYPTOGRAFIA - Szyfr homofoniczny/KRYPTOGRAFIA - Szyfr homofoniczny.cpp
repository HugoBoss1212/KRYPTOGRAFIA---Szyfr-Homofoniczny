// KRYPTOGRAFIA - Szyfr homofoniczny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <tuple>
#include <unordered_set>
#include <map>

struct homofon {
	bool operator==(homofon const& rhs) const { return a && occurance; }
	bool operator<(homofon const& rhs) const { return std::tie(rhs.a, rhs.occurance) > std::tie(a, occurance); }
	char a;
	int occurance;
};

std::map<char, std::vector<int>> generate_tab(std::string input) {
	srand(time(NULL));
	std::set<homofon> set;
	std::map<char, std::vector<int>> return_map;
	int j = 0;
	for (int i = 0; i < input.length(); i++) {
		int occurrance = 0,
			pos = 0;
		while ((pos = input.find(input[i], pos)) != std::string::npos) {
			++occurrance;
			++pos;
		}
		set.insert(homofon{ input[i], occurrance });
	}
	std::cout << "Tablica homofonow: \n";
	for (homofon s : set) {
		std::cout << s.a << ": (";
		std::vector<int> temp_vec;
		for (int i = 0; i < s.occurance + 1; i++) {
			int temp = (rand() % 10+(10*j) + (10*j));
			temp_vec.push_back(temp);
			std::cout<< temp <<", ";
			++j;
		}
		return_map[s.a] = temp_vec;
		std::cout << ")" << std::endl;
	}
	std::cout << "\n";

	return return_map;
}

std::string szyfruj(std::string input, std::map<char, std::vector<int>> map) {
	std::string return_buffer;
	srand(time(NULL));
	int temp;
	for (char i : input) {
		temp = map[i].at(rand() % map[i].size());
		return_buffer += std::to_string(temp) + " ";
	}
	return return_buffer;
}

std::string deszyfruj(std::string input, std::map<char, std::vector<int>> map, int len) {
	std::string return_buffer;
	int i = 0;
	for (int j = 0; j < len; j++) {
		std::string temp;
		while (i < input.length() && input[i] != 32) {
			temp += input[i];
			i++;
		}
		i++;
		for (std::map<char, std::vector<int>>::iterator it = map.begin(); it != map.end(); ++it) {
			for (int l = 0; l < map[it->first].size(); l++) {
				std::string temp_str;
				if (map[it->first].at(l) == std::stoi(temp)) {
					temp_str = it->first;
					return_buffer += temp_str;
				}
			}
		}
	}

	return return_buffer;
}

int main() {
	std::string input;
	std::map<char, std::vector<int>> map;
	std::cout << "Podaj tekst jawny do zaszyfrowania: \n\t";
	std::getline(std::cin, input);
	int len = input.length();
	for (int i = 0; i < input.length(); i++) { input[i] = tolower(input[i]); }
	map = generate_tab(input);
	std::cout << "Wynik szyfryzacji:\n\t" + szyfruj(input, map) + "\n";
	std::cout << "Podaj szyfrogram do deszyfryzacji: \n\t";
	std::getline(std::cin, input);
	std::cout << "\nWynik deszyfryzacji:\n\t" + deszyfruj(input, map, len) + "\n";

	system("PAUSE");
	return 0;
}