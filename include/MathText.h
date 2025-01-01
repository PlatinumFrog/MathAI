#pragma once
#include <iostream>
#include <random>
#include <string>
#include <cmath>

class MathTextGenerator {
	// Numbers: 0-9, Lowercase: 10-35, Uppercase: 36-61, Isolators: 62-69, Separators: 70-76, Operators: 77-81, Equais: 82
	const char* alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()[]{}<>.,;_|\'\"+-/*^=";
	// Generate a random alphanumeric character. flags & 1 for lowercase, flags & 2 for uppercase, flags & 4 for numbers, can have multiple flags
	const char randomAlphanumeric(const uint8_t flags) {
		switch (flags) {
		case 1: return alphabet[rand() % 26 + 10];
		case 2: return alphabet[rand() % 26 + 36];
		case 3: return alphabet[rand() % 52 + 10];
		case 4: return alphabet[rand() % 10];
		case 5: return alphabet[rand() % 36];
		case 6:
		{
			uint32_t id = rand() % 36;
			return alphabet[id > 9 ? id + 26 : id];
		}
		case 7: return alphabet[rand() % 62];
		default: return alphabet[rand() % 62];
		}
	}

	std::string randomAlphanumericSet(const uint8_t flags, const uint32_t length) {
		if (length == 0) return "";
		std::string output = "";
		switch (flags) {
		case 1: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 26 + 10]; return output; }
		case 2: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 26 + 36]; return output; }
		case 3: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 52 + 10]; return output; }
		case 4: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 10]; return output; }
		case 5: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 36]; return output; }
		case 6:
		{
			for (uint32_t i = 0; i < length; i++) {
				uint32_t id = rand() % 36;
				output += alphabet[id > 9 ? id + 26 : id];
			}
			return output;
		}
		case 7: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 62]; return output; }
		default: { for (uint32_t i = 0; i < length; i++) output += alphabet[rand() % 62]; return output; }
		}
	}

public:
	// Generate a variable matching the regex: [a-zA-Z][a-zA-Z0-9]*((\^[a-zA-Z0-9]+)?_[a-zA-Z0-9]+)?
	std::string variable(
		const uint8_t allowedCases = 1, // lowercase: 1, UPPERCASE: 2, numbers: 4 -> cannot be 4
		const uint8_t nameLength = 1, // Length of the variable name
		const uint8_t subscriptLength = 0, // Length of the subscript, if zero, no subscript
		const uint8_t superscriptLength = 0	// Length of the superscript, if subscriptLength is zero, superscriptLength must be zero, if zero, no superscript
	) {
		std::string output = ""; // Output string
		output += randomAlphanumeric(allowedCases & 3); // First character
		output += randomAlphanumericSet(allowedCases, nameLength - 1); // Rest of the name
		if (subscriptLength > 0) { // Subscript
			if (superscriptLength > 0) { // Superscript only if subscript exists
				output += '^';
				output += randomAlphanumericSet(allowedCases, superscriptLength);
			}
			output += '_';
			output += randomAlphanumericSet(allowedCases, subscriptLength);
		}
		return output;
	}

	// Generate a sequence of variables and return a ptr to the array. REMEMBER TO DELETE THE POINTER
	std::string* variablesNumericSequence(
		const uint8_t allowedCases = 1, // lowercase: 1, UPPERCASE: 2, numbers: 4 -> cannot be 4
		const uint8_t nameLength = 1, // Length of the variable name
		const uint8_t subscriptLength = 0, // Length of the subscript, if zero, no subscript
		const uint8_t superscriptLength = 0,	// Length of the superscript, if subscriptLength is zero, superscriptLength must be zero, if zero, no superscript
		const uint32_t count = 1 // Number of variables
	) {
		if (count == 0) return nullptr;
		std::string var = variable(allowedCases, nameLength, subscriptLength, superscriptLength);
		std::string* output = new std::string[count];
		if (subscriptLength == 0) for (uint32_t i = 0; i < count; i++) { output[i] = var + "_" + std::to_string(i); }
		else for (uint32_t i = 0; i < count; i++) { output[i] = var + std::to_string(i); }
		return output;
	}

	// Generate a random integer between min and max as a string
	std::string randomInteger(const int32_t min, const int32_t max) {
		return std::to_string(rand() % (max - min + 1) + min);
	}

	// Generate a sum of variables and integers in any random order
	std::string sum(
		const uint8_t allowedCases = 1, // lowercase: 1, UPPERCASE: 2, numbers: 4 -> cannot be 4
		const uint8_t nameLength = 1, // Length of the variable name
		const uint8_t subscriptLength = 0, // Length of the subscript, if zero, no subscript
		const uint8_t superscriptLength = 0,	// Length of the superscript, if subscriptLength is zero, superscriptLength must be zero, if zero, no superscript
		const bool isSequence = false, // If true, the variables will be subscripted with numbers in a sequence
		const uint32_t nVariables = 1, // Number of variables
		const uint32_t nIntegers = 1, // Number of integers
		const int32_t minInteger = -100, // Minimum integer value
		const int32_t maxInteger = 100 // Maximum integer value
	) {
		if (nVariables == 0 && nIntegers == 0) return ""; // If no variables or integers, return an empty string
		else {
			// Create an array of terms
			std::string* terms = new std::string[nVariables + nIntegers];

			// Place the integers in the terms array randomly
			for (uint32_t i = 0; i < nIntegers; i++) {
				uint32_t id = rand() % (nVariables + nIntegers);
				while (terms[id] != "") id = rand() % (nVariables + nIntegers);
				terms[id] = randomInteger(minInteger, maxInteger);
			}

			// If the variables are in a sequence, place them in order in empty spots in the terms array
			if (isSequence) {
				std::string* variables = variablesNumericSequence(allowedCases, nameLength, subscriptLength, superscriptLength, nVariables);
				uint32_t id = 0;
				for (uint32_t i = 0; i < nVariables + nIntegers; i++) if (terms[i] == "") terms[i] = variables[id++];
				delete[] variables;
			} else {
				// Otherwise for each empty term, generate a variable
				for (uint32_t i = 0; i < nVariables + nIntegers; i++) if (terms[i] == "") terms[i] = variable(allowedCases, nameLength, subscriptLength, superscriptLength);
			}
			// Concatenate the terms into a sum
			std::string output = terms[0];
			for (uint32_t i = 1; i < nVariables + nIntegers; i++) output += (terms[i][0] == '-') ? " - " + terms[i].erase(0, 1) : " + " + terms[i];
			delete[] terms;
			return output;
		}
	}
};

struct DataPair { 

	// Input and output strings
	std::string input, output;

	// Information about the characters in the input and output strings
	// Types: Constant, Scalar, Vector, Matrix, Operator, Function, Parameter, Separator, Isolator
	std::vector<uint8_t> inputTypes, outputTypes;

	// Expression level or priority of each expression. Opening isolator increases and closing isolator decreases. Should be zero at either end of the expression.
	std::vector<uint8_t> inputLevels, outputLevels;

	// Priority of each token, based on operator precedence and order of appearence in the expression.
	std::vector<uint8_t> inputPriority, outputPriority;

	// Each tuple of (character, type, level, priority) is converted into a token of 4 floats.
	std::vector<float> inputTokens, outputTokens;
};