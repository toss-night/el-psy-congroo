#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> generator(const std::string& chrs) {
    std::vector<std::string> combs;
	int countComb = 1;
	for (int i = 0; i < chrs.size(); i++) {
		countComb *= chrs.size() - i;		
	}
	std::string word = "";
	for (int j = 0; j < countComb; j++) {		
		
		
	}
	return combs;
}

int main() {
	std::string chrs = "abc";
	int contComb = 1;
	for (int i = 0; i < chrs.size(); i++) {
		contComb *= chrs.size() - i;
	}
	std::cout << contComb << "\n";
}

