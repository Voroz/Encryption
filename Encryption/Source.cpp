#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EncryptionData {
public:
	EncryptionData() :
		n(0),
		r(0),
		d(0),
		message(0) {};
	EncryptionData(long long int n, long long int r, long long int d, long long int message) :
		n(n),
		r(r),
		d(d),
		message(message){};
	long long int n;
	long long int r;
	long long int d;
	long long int message;
};

int gcd(int a, int b) {
	int r = a % b;
	if (r == 0) {
		return b;
	}
	return gcd(b, r);
}

int gcdExtended(int a, int b, long long int &x, long long int &y) {
	// Base Case
	if (a == 0){
		x = 0;
		y = 1;
		return b;
	}

	long long int x1, y1; // To store results of recursive call
	int gcd = gcdExtended(b%a, a, x1, y1);

	// Update x and y using results of recursive
	// call
	x = y1 - (b / a) * x1;
	y = x1;

	return gcd;
}

int moduloPow(long long int toModulo, long long int power, long long int modulo) {
	long long int temp = 1;
	for (int i = 0; i < power; i++) {
		if (temp*toModulo < 0) {
			cout << "Error: Overflow IN moduloPow()" << endl;
			return 0;
		}
		temp = (temp*toModulo) % modulo;
	}
	return temp;
}

int findKey(int p, int q, int e) {
	long long int n = p*q;
	long long int r = (p - 1)*(q - 1);

	if (gcd(e, r) != 1) {
		cout << "Error: gcd(e, r) != 1 IN findKey()" << endl;
		return 0;
	}

	long long int x = 0;
	long long int y = 0;
	gcdExtended(e, r, x, y);
	long long int d = x;
	if (x < 0) {
		d = (r + x) % r;
	}
	return d;
}

EncryptionData encrypt(int message, int p, int q, int e) {
	long long int n = p*q;
	long long int r = (p - 1)*(q - 1);

	if (gcd(e, r) != 1) {
		cout << "Error: gcd(e, r) != 1 IN encrypt()" << endl;
		return EncryptionData();
	}

	int d = findKey(p, q, e);

	long long int encryptedMessage = moduloPow(message, e, n);
	return EncryptionData(n, r, d, encryptedMessage);
}

int decrypt(long long int message, long long int d, long long int n) {
	int decryptedMessage = moduloPow(message, d, n);
	return decryptedMessage;
}


int main() {
	int p = 1051;
	int q = 1307;
	int e = 13;
	int d = findKey(p, q, e);

	cout << "Encryption information:" << endl;
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
	cout << "e: " << e << endl;
	cout << "d: " << d << "\n\n";

	while (1) {
		cout << "Enter message to encrypt:" << endl;
		string strMessage = "";
		getline(std::cin, strMessage);
		cout << endl;

		// Encrypt string and save encrypted integers to vector eData
		vector<EncryptionData> eData;
		for (int i = 0; i < strMessage.length(); i++) {
			eData.push_back(encrypt(strMessage[i], p, q, e));
		}

		cout << "Encrypted message: " << endl;
		for (int i = 0; i < eData.size(); i++) {
			cout << eData[i].message << endl;
		}
		cout << endl;

		// Decrypt message into a string
		cout << "Decrypted message:" << endl;
		string decryptedMessage = "";
		for (int i = 0; i < eData.size(); i++) {
			decryptedMessage += decrypt(eData[i].message, eData[i].d, eData[i].n);
		}
		cout << decryptedMessage << "\n\n\n\n";
	}

	return 0;
}