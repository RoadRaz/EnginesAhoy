#pragma once
#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H
#include <cstdlib>
#include <iostream>
#include <ctime>

class RandomUtil {
public:
	static int RandI(int min, int max) {
		if (min < max) {
			return((rand() % (max - min)) + min);
		}
		return 0;
	}
};
#endif