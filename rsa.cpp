#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

bool isPrime(int num){
	if(num == 1 || num == 4)
		return false;
	for(int i = 2; i < num / 2; i++){
		if(num % i == 0)
			return false;
	}
	return true;
}

int generateRandomPrime(int low, int high){
	vector<int> primes;
	for(int i = low; i < high; i++){
		if(isPrime(i))
			primes.push_back(i);
	}

	int place = rand() % primes.size();
	return primes[place];
}

pair<int, int> euclid(int large, int small){
	vector<int> factors;
	div_t divresult;
	int d, e;
	bool odd = true;
	while(divresult.rem != 1){
		divresult = div(large, small);
		factors.push_back(divresult.quot);
		large = small;
		small = divresult.rem;
	}

	reverse(factors.begin(), factors.end());
	d = 1;
	e = factors[0];

	for(int i = 1; i < factors.size(); i++){
		if(odd){
			d += factors[i] * e;
			odd = !odd;
		} else {
			e += factors[i] * d;
			odd = !odd;
		}
	}

	return make_pair(e, d);
}

int exp(int base, int ex){
	int num = 1;
	for(int i = 0; i < ex; i++){
		num *= base;
	}
	return num;
}

int largetwo(int num){
	int test = 1;
	while(test <= num)
		test *= 2;
	if(test == 1) return test;
	else return test / 2;
}

int powertwo(int num){ //i designed so it works with only powers of two
	int counter = 0;
	while(num != 1){
		num /= 2;
		counter++;
	}
	return counter;
}

int expmod(int base, int ex, int mod){
	vector<int> powers;
	int a;
	while(ex > 0){
		a = largetwo(ex);
		powers.push_back(powertwo(a));
		ex -= a;
	}

	vector<int> x;
	x.push_back(base % mod);
	for(int i = 1; i <= powers[0]; i++){
		x.push_back(exp(x[i-1],2) % mod);
	}
	
	reverse(powers.begin(), powers.end());
	a = x[powers[0]];

	for(int i = 1; i < powers.size(); i++){
		a *= x[powers[i]];
		a %= mod;
	}
	
	return a;
}

int main(int argc, char* argv[]){

	int n, p, q, totiN, d, e, message, encrypt, s;
	cout << "Press E to Encrypt and D to Decrypt" << endl;
	char input;
	cin >> input;

	
	if(input == 'E'){
		srand(time(NULL));
		p = generateRandomPrime(2, 100);
		q = generateRandomPrime(2, 100);

		n = p * q;
		totiN = (p-1) * (q-1);

		e = generateRandomPrime(10000, 20000);

		pair<int, int> eu = euclid(totiN, e); //I legit have no idea how euclid is useful here
		if(eu.first < eu.second)
			d = eu.first;
		else
			d = eu.second;

		cout << "Public Key N: " << n << endl << "Public Key E: " << e << endl;
		cout << "Private Key D: " << d << endl;

		cout << "Send number to be encrypted(less than N)";
		cin >> message;

		encrypt = expmod(message, e, n);
		cout << "Encrypted Message: " << encrypt;

		/*cout << "NUMBER: " << (e * d - 1) % totiN << endl; //should be 0 for the code to worku
		cout << totiN << ' ' << e << ' ' << eu.first << ' ' << eu.second;*/
	}
	else if(input == 'D'){
		cout << "Enter encrypted message: ";
		cin >> encrypt;
		cout << "Enter private key D: ";
		cin >> d;
		cout << "Enter public key N: ";
		cin >> n;

		message = expmod(encrypt, d, n);
		cout << "Decrypted message: " << message << endl;
	} else {
		cout << "Unrecognized input." << endl;
	}


}