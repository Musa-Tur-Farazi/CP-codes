#include<bits/stdc++.h>
using namespace std;

template<typename T>
void SubsetZetaTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i] += v[i ^ j];
	}
}

template<typename T>
void SubsetMobiusTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i] -= v[i ^ j];
	}
}

template<typename T>
void SupersetZetaTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i ^ j] += v[i];
	}
}

template<typename T>
void SupersetMobiusTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i ^ j] -= v[i];
	}
}

template<typename T>
void DivisorZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = 1; i * p <= n; i++)
			v[i * p] += v[i];
	}
}

template<typename T>
void DivisorMobiusTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = n / p; i; i--)
			v[i * p] -= v[i];
	}
}
/* Linear Sieve, O(n) */
vector<int> PrimeEnumerate(int n) {
	vector<int> P; vector<bool> B(n + 1, 1);
	for (int i = 2; i <= n; i++) {
		if (B[i]) P.push_back(i);
		for (int j : P) { if (i * j > n) break; B[i * j] = 0; if (i % j == 0) break; }
	}
	return P;
}

template<typename T>
void MultipleZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = n / p; i; i--)
			v[i] += v[i * p];
	}
}

template<typename T>
void MultipleMobiusTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = 1; i * p <= n; i++)
			v[i] -= v[i * p];
	}
}

template<typename T>
vector<T> AndConvolution(vector<T> A, vector<T> B) {
	SupersetZetaTransform(A);
	SupersetZetaTransform(B);
	for (int i = 0; i < A.size(); i++) A[i] *= B[i];
	SupersetMobiusTransform(A);
	return A;
}

template<typename T>
vector<T> OrConvolution(vector<T> A, vector<T> B) {
	SubsetZetaTransform(A);
	SubsetZetaTransform(B);
	for (int i = 0; i < A.size(); i++) A[i] *= B[i];
	SubsetMobiusTransform(A);
	return A;
}

template<typename T>
vector<T> GCDConvolution(vector<T> A, vector<T> B) {
    MultipleZetaTransform(A);
    MultipleZetaTransform(B);
    for (int i = 0; i < A.size(); i++) A[i] *= B[i];
    MultipleMobiusTransform(A);
    return A;
}

template<typename T>
vector<T> LCMConvolution(vector<T> A, vector<T> B) {
    DivisorZetaTransform(A);
    DivisorZetaTransform(B);
    for (int i = 0; i < A.size(); i++) A[i] *= B[i];
    DivisorMobiusTransform(A);
    return A;
}


int main(){
    int n; cin >> n;
    vector<int>a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m)


}
