#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>

#include "MathText.h"

class Transformer {
	std::vector<uint8_t> tokens;
	std::vector<uint8_t> precedence;
	std::vector<float> attention;
public:

	Transformer() {}

	std::string run(std::string input) {
		
	}

	float train(std::string input, std::string output) {

	}
};