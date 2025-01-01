#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>

#include "MathText.h"



// 
class Transformer {
	std::vector<uint8_t> tokenLevel; // Level of expression in a parenthesis. opening parenthesis increases level, and closing parenthesis decreases level
	std::vector<uint8_t> tokenPriority; // The tokens priority is based on operator precedence and other factors
	std::vector<float> attention;
	std::vector<float> feedForward;

public:

	Transformer() {}

	std::string run(std::string input) {
		
	}

	float train(std::string input, std::string output) {
		for (uint32_t i = 0; i < input.size(); i++) {
			
		}
	}
};