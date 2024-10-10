/** /#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <crtdbg.h>//msvc only

template <class T>
struct Memory {
	T* M = NULL;
	size_t L = 0;
};
template<class T>
Memory<T> ConstructMemroy(size_t N) {
	void* P = calloc(N, sizeof(T));
	Memory<T> M;
	M.M = (T*)P;
	M.L = N;
	return M;
}

template <class T>
bool Free(Memory<T>& In) {
	free(In.M);
	In.M = NULL;
	In.L = 0;
	return true;
}

template <class T>
T* Index(Memory<T>& In,size_t Pos) {
	return Pos >= In.L ? NULL:&In.M[Pos];
}

template <class T>
bool ReAllocateMemory(Memory<T>& In, size_t L) {
	void* P = realloc(In.M, L*sizeof(T));
	if (P != &In.M[0]) {
		In.M = (T*)P;
		In.L = L;
	}
	int X = ((int)In.L) - ((int)L);
	if (X > 0) {
		memset(In.M + In.L * sizeof(T), 0, X);
	}

	return true;
}

template <class T>
size_t Size(Memory<T>& In) {
	return In.L;
}
/**/

#include"MemoryAllocator.h"

template <class T>
T* New(size_t N) {
	return (T*)calloc(N, sizeof(T));
}

template <class T>
bool Delete(T** M) {
	free(*M);
	(*M) = NULL;

	return true;
}

int main() {
	auto M = New<int>(1);

	Delete(&M);

	return 0;
}

/** /
int main() {
	auto A = ConstructMemroy<int>(16);

	auto B = Index(A, 8);

	(*B) = 8;

	ReAllocateMemory<int>(A, 32);

	for (size_t i = 0; i < Size(A); i++) {
		(*Index(A, i)) = (int)i;
	}
	for (size_t i = 0; i < Size(A); i++) {
		std::cout << *Index(A, i) << std::endl;
	}
	_CrtDumpMemoryLeaks();//msvc only
	Free(A);

	_CrtDumpMemoryLeaks();//msvc only
}
/**/