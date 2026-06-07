#include <iostream>
#include <vector>
#include <string>

void generator(const std::string& chrs, std::vector<std::string>& combs) {	
	if (chrs.size() <= 1) combs.push_back(chrs);
	else {
		for (size_t i = 0; i < chrs.size(); i++) {			
			std::string str = chrs.substr(0, i) + chrs.substr(i + 1);
			std::vector<std::string> tempCombs;		
			generator(str, tempCombs);			
			for (std::string s : tempCombs) {
				std::string comb = chrs[i] + s; 
				combs.push_back(comb); 
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	std::vector<std::string> combs;
	generator("аувоодлир", combs);
	for (std::string comb : combs) {
		std::cout << "K" << comb << "\n";
	}
}

