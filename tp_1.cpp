#include <iostream>
#include <algorithm>

//дописать разность множеств
struct Point {

	int x;
	int y;
	int z;
	Point() : x(0), y(0), z(0){}

	Point(int x, int y, int z): x(x), y(y), z(z){}
	
	bool operator<(const Point& other) const {
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return z < other.z;
	}

	bool operator==(const Point& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& p) {
		os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
		return os;
	}
};


template <typename T> 
class Set {

private:
	size_t size;
	size_t capacity;
	T* elements;

public:
	Set(size_t initial_capacity = 5) : size(0), capacity(initial_capacity), elements(new T[initial_capacity]){}

	Set(const Set& other) : elements(new T[other.capacity]), size(other.size), capacity(other.capacity) {
		for (int i = 0; i < other.size; i++) {
			elements[i] = other.elements[i];
		}
	}

	~Set() {
		delete[] elements;
	}

	void insert(const T& value) {

		if (!find(value)) {
			if (size == capacity) {
				capacity *= 2;
				T* new_elements = new T[capacity];
				for (size_t i = 0; i < size; i++) {
					new_elements[i] = elements[i];
				}
				delete[] elements;
				elements = new_elements;
			}
			elements[size++] = value; 
			std::sort(elements, elements + size);
		}
	}


	bool find(const T& value) {

		for (size_t i = 0; i < size; i++) {
			if (elements[i] == value){
				return true;
			}
		}
		return false;
	}

	bool find_in_a_set(const T& value) {

		for (size_t i = 0; i < size; i++) {
			if (elements[i] == value) {
				std::cout << "Element found at index:" << i << std::endl;
				return true;
			}
		}
		return false;
	}

	int size_of_set() const {

		return this->size;
	}

	Set& set_union(const Set& s, const Set& s1) {

		if (s.size == 0 || s1.size == 0) {
			throw ("Error, cannot union with an empty set");
		}

		Set result = (s1.size + s.size);

		for (size_t k = 0; k < s.size; k++) {
			result.insert(s.elements[k]);
		}

		for (size_t i = 0; i < s1.size; i++) {
			result.insert(s1.elements[i]);
		}

		*this = result;
		return *this;
	}

	Set& set_diff(Set& s, Set& s1) {

		for (size_t i = 0; i < s.size; i++) {
			if (!s1.find(s.elements[i])) {
				insert(s.elements[i]);
			}
		}

		return *this;
	}

	Set& operator=(const Set& s) {

		if (this != &s) {

			delete[] elements;
			size = s.size;
			capacity = s.capacity;
			elements = new T[capacity];

			for (size_t i = 0; i < size; i++) {
				elements[i] = s.elements[i];
			}
		}
		std::sort(elements, elements + size);
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& os, const Set<T>& s) {

		os << "{ ";
		for (size_t j = 0; j < s.size; j++) {
			os << s.elements[j];

			if (j < s.size - 1) {
				os<< ", ";
			}
		}
		os << " }";

		return os;
	}

};


int main() {

	/*Set <std::string> str1;
	str1.insert("jack daniels");
	str1.insert("cabernet");
	str1.insert("rum");
	str1.insert("apple");

	Set <std::string> str2;
	str2.insert("alcohol is evil");
	str2.insert("apple");
	str2.insert("juice");

	Set <std::string> str3;

	std::cout << "Set str1: " << str1 << "\n";
	std::cout << "Set str2: " << str2 << "\n";
	std::cout << "Result of searching element rum: " << str1.find_in_a_set("rum") << std::endl;
	фыфыstd::cout << "Result of diff str1&str2: " << str3.set_diff(str1, str2) << std::endl;
	*/
	Set<int> a;
	a.insert(4);
	a.insert(8);
	a.insert(2);
	a.insert(0);

	Set <int> b;
	b.insert(2);
	b.insert(78);
	b.insert(-255);
	b.insert(99);

	Set <int> result;

	result.set_union(a, b);

	Set <int> result3;
	result3.set_diff(b, a);
	
	Set <int> l;
	Set <int> p;

	std::cout << "Set a: " << a << "\n";
	std::cout << "Set l: " << l << "\n";
	std::cout << "Set b: " << b << "\n";
	std::cout << "Res of uniting:" << result << "\n";
	std::cout << "Res of difference(b - a):" << result3 << "\n";
	try {
		Set<int> united = p.set_union(a, l);
		std::cout << "Union of int sets: " << united << std::endl;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	return 0;
}