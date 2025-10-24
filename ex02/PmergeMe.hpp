#pragma once

#include <ctime>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <exception>
#include <iostream>


class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deque;
public:
	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe &operator=(const PmergeMe &rhs);
	~PmergeMe();

	void addNumber(int n);
	void initVector();
	void initDeque();

	void printBefore(char **argv) const;
	void printAfter() const;

	std::vector<int> getVector() const;
	std::deque<int> getDeque() const;
	class NumNegative : public std::exception {
			public:
				const char *what() const throw();
		};
};



// You must create a program with these constraints:
// • The name of the program is PmergeMe.
// • Your program must be able to use a positive integer sequence as an argument.
// • Your program must use the merge-insert sort algorithm to sort the positive integer
// sequence.
// To clarify, yes, you need to use the Ford-Johnson algorithm.
// (source: Art Of Computer Programming, Vol.3. Merge Insertion,
// Page 184.)
// • If an error occurs during program execution, an error message should be displayed
// on the standard error.
// You must use at least two different containers in your code to
// validate this exercise. Your program must be able to handle at
// least 3000 different integers.
// It is strongly advised to implement your algorithm for each container
// and thus to avoid using a generic function.
// Here are some additional guidelines on the information you should display line by line
// on the standard output:
// • On the first line you must display an explicit text followed by the unsorted positive
// integer sequence.
// • On the second line you must display an explicit text followed by the sorted positive
// integer sequence.
// • On the third line, you must display an explicit message indicating the time taken
// by your algorithm, specifying the first container used to sort the positive integer
// sequence.
// • On the last line you must display an explicit text indicating the time used by
// your algorithm by specifying the second container used to sort the positive integer
// sequence.

// The format for the display of the time used to carry out your sorting
// is free but the precision chosen must allow to clearly see the
// difference between the two containers used.
// Here is an example of standard use:
// $> ./PmergeMe 3 5 9 7 4
// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us
// $> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// Before: 141 79 526 321 [...]
// After: 79 141 321 526 [...]
// Time to process a range of 3000 elements with std::[..] : 62.14389 us
// Time to process a range of 3000 elements with std::[..] : 69.27212 us
// $> ./PmergeMe "-1" "2"
// Error
// $> # For OSX USER:
// $> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
// [...]
// $>
// The indication of the time is deliberately strange in this example.
// Of course you have to indicate the time used to perform all your
// operations, both the sorting part and the data management part.
// Warning: The container(s) you used in the previous exercises are
// forbidden here.
// The management of errors related to duplicates is left to your
// discretion.



9 3 7 2 8                                                   12 5 9 1 7 6 3 8 10 4 2 11
                                                            
divide [9 3 7 2 8]                                          divide [12 5 9 1 7 6 3 8 10 4 2 11]
	left [9 3 7]  rifgt [2 8]                               	left [12 5 9 1 7 6]  rifgt [3 8 10 4 2 11]
                                                            
                                                            
        [9     3     7]   [2     8]                                   [12 5 9 1 7 6]                      [3 8 10 4 2 11]
         \   /     /         /                                           /          \                     /            \ 
          3 9   7           /                                       [12 5 9]       [1 7 6]              3 8 10        4 2 11
           \   /           /                                        /    \         /    \              /    \        /    \
           3  7   9       /                                     [12 5]   [9]   [1 7]     [6]       [3 8]    [10]  [4 2]    [11]
            \     /      /                                           sort            sort               sort          sort
            [3 7 9]     /                                   [5  9  12]       [1  6  7]           [3  8  10]      [2  4  11]
           /       \   /                                             mergeVector                          mergeVector
      [9 3 7]     [2 8]                                              1 5 6 7 9 12                        2 3 4 8 10 11
           \       /                                                                    mergeVector
            [2 3 7 8 9]                                                         1 2 3 4 5 6 7 8 9 10 11 12
                                                            
                                                            
mergeVector                                                 mergeVector
[9 3 7] y [2 8]                                             [12 5 9 1 7 6] y [3 8 10 4 2 11]
	left                                                    	left   [12 5 9] [1 7 6]
		9 + 3 -> 3 9                                        		12 + 5 -> 5 12
		3 9 + 7 -> 3 7 9                                    		5 12 + 9 -> 5 9 12
	left result [3 7 9]                                     		5 9 12 + 1 -> 1 5 9 12
	right                                                   		1 5 9 12 + 7 -> 1 5 7 9 12
		2 + 8 -> 2 8                                        		1 5 7 9 12 + 6 -> 1 5 6 7 9 12
right result [2 8]                                      		left retsult [1 5 6 7 9 12]
	final retsult                                           
		3 7 9 + 2 8 -> 2 3 7 8 9                            right [3 8 10] [4 2 11]
                                                            	3 + 8 -> 3 8
                                                            	3 8 + 10 -> 3 8 10
                                                            	3 8 10 + 4 -> 3 4 8 10
                                                            	3 4 8 10 + 2 -> 2 3 4 8 10
                                                            	2 3 4 8 10 + 11 -> 2 3 4 8 10 11
                                                            right retsult [1 5 6 7 9 12]
                                                            
                                                            final result [1 5 6 7 9 12] + [2 3 4 8 10 11] -> 1 2 3 4 5 6 7 8 9 10 11 12
