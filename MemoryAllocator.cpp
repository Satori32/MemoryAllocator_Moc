#include"MemoryAllocator.h"

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
T* Index(Memory<T>& In, size_t Pos) {
	return Pos >= In.L ? NULL : &In.M[Pos];
}

template <class T>
bool ReAllocateMemory(Memory<T>& In, size_t L) {
	void* P = realloc(In.M, L * sizeof(T));
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