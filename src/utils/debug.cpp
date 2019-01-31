#include "debug.h"

void printUnsignedIntArray(const char * name, const unsigned int * vals, const unsigned int length) {
	cout << name << ": [ ";

	for (unsigned int i = 0; i < length; i++) {
		cout << *(vals + i);

		if (i != length - 1) {
			cout << " , ";
		}
	}

	cout << " ]\n";
}

void printFloatArray(const char * name, const float * vals, const unsigned int length) {
	cout << name << ": [ ";

	for (unsigned int i = 0; i < length; i++) {
		cout << *(vals + i);

		if (i != length - 1) {
			cout << " , ";
		}
	}

	cout << " ]\n";
}

void printUnsignedCharArray(const char * name, const unsigned char * vals, const unsigned int length) {
	cout << name << ": [ ";

	for (unsigned int i = 0; i < length; i++) {
		cout << (int)*(vals + i);

		if (i != length - 1) {
			cout << " , ";
		}
	}

	cout << " ]\n";
}