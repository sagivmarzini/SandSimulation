#pragma once
#include <random>

class Random
{
public:
	static void seed(unsigned int value);

	static int intInRange(int min, int max);
	static float floatInRange(float min, float max);

	template <typename Container>
	static auto randomItem(const Container& container) -> decltype(container[0])
	{
		if (container.empty())
			throw std::runtime_error("Can't pick a random item from an empty container");

		int index = intInRange(0, static_cast<int>(container.size()) - 1);
		return container[index];
	}

private:
	static inline std::mt19937 gen{ std::random_device{}() };
};
