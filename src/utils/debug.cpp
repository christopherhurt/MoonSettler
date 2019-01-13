#include "debug.h"

void printFloatArray(const char * name, float * vals, unsigned int length) {
	cout << name << ": [ ";

	for (unsigned int i = 0; i < length; i++) {
		cout << (vals + i);

		if (i != length - 1) {
			cout << " , ";
		}
	}

	cout << " ]\n";
}