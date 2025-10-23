#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) : _vec(copy._vec), _deque(copy._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &p) {
	if (this != &p) {
		_vec = p._vec;
		_deque = p._deque;
	}
	return *this;
}

const char *PmergeMe::NumNegative::what() const throw() {
	return "error the number is negative";
}


void PmergeMe::addNumber(int num) {
	if (num < 0)
		throw NumNegative();
	_vec.push_back(num);
	_deque.push_back(num);
}

static void mergeVector(std::vector<int> &v, int left, int right, int mid) {
	std::vector<int> temp;
	int i = left;
	int j = mid +1;

	while (i <= mid && j <= right) {
		if (v[i] < v[j])
			temp.push_back(v[i++]);
		else
			temp.push_back(v[j++]);
	}
	while (i <= mid)
		temp.push_back(v[i++]);
	while (j <= right)
		temp.push_back(v[j++]);
	for (int x = 0; x < (int)temp.size(); ++x)
		v[left + x] = temp[x];
	
}

static void sortVector(std::vector<int> &v, int left, int right) {
	if (right - left <= 10) {
		for (int x = left +1; x <= right; ++x){
			int key = v[x];
			int y = x -1;

			while (y >= left && v[y] > key)	{
				v[y+1] = v[y];
				y--;				
			}
			v[y+1] = key;
		}
		return;
	}
	int mid = (left + right) / 2;
	sortVector(v, left, mid);
	sortVector(v, mid + 1, right);
	mergeVector(v, left, mid, right);
}

void PmergeMe::initVector() {
	if (_vec.size() > 1)
		sortVector(_vec, 0, _vec.size() -1);
}

static void mergeDeque(std::deque<int> &d, int left, int right, int mid) {
	std::deque<int> temp;
	int x = left;
	int y = mid +1;

	while (x <= mid && y <= right) {
		if (d[x] < d[y])
			temp.push_back(d[x++]);
		else
			temp.push_back(d[y++]);
	}
	while (x <= mid)
		temp.push_back(d[x++]);
	while (y <= right)
		temp.push_back(d[y++]);

	for (int i = 0; i < (int)temp.size(); i++) {
		d[left+i] = temp[i];
	}
	
}

static void sortDeque(std::deque<int> &d, int left, int right) {
	if (right - left <= 10) {
		for (int x = left +1; x <= right; ++x) {
			int key = d[x];
			int y = x -1;
			while (y >= left && d[y] > key) {
				d[y +1]	= d[y];
				y--;		
			}
			d[y +1] = key;
		}
		return;
	}
	int mid = (left+right) / 2;
	sortDeque(d, left, mid);
	sortDeque(d, mid +1, right);
	mergeDeque(d, left, mid, right);
}

void PmergeMe::initDeque() {
	if (_deque.size() > 1)
		sortDeque(_deque, 0, _deque.size() - 1);
}

void PmergeMe::printBefore(char **argv) const {
	for (int i = 1; argv[i]; ++i)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::printAfter() const {
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << _vec[i] << " ";
	std::cout << std::endl;
}

std::vector<int> PmergeMe::getVector() const {
	return _vec;
}

std::deque<int>  PmergeMe::getDeque()  const {
	return _deque;
}