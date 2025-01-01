#include "../include/MathText.h"

constexpr uint32_t N_GENERATIONS = 10;
constexpr uint32_t MAX_VARIABLES = 3;

int main(int argc, char* argv[]) {

	MathTextGenerator generator;

	std::srand(std::time(nullptr));
	for (uint32_t i = 0; i < N_GENERATIONS; i++) {
		std::string sum = generator.sum(5, 1, 0, 0, true, 2, 1);
		std::cout << sum << '\n';
	}

	std::cout << std::endl;

	return 0;

}