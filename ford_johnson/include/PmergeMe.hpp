#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <algorithm>
# include <vector>
# include <bits/stdc++.h>
# include <limits>

class	PmergeMe
{
	public:
		static void		sort(std::vector<int> &numbers);

		static void		sort(std::deque<int> &numbers);

	protected:

	private:
						PmergeMe(void);
						~PmergeMe(void);
						PmergeMe(const PmergeMe &otherPmergeMe);
		PmergeMe		&operator=(const PmergeMe &otherPmergeMe);
		static size_t	jacobsthalIndex(size_t index);

// *********************************************************************
// ************************* VECTOR ************************************
// *********************************************************************

		static void		makePairs(std::vector<int> &numbers);
		static void		mergeSort(std::vector<int> &numbers, size_t left, size_t right);
		static void		merge(std::vector<int> &numbers, size_t left, size_t mid, size_t right);
		static void		initializeSubSequence(const std::vector<int> &numbers, std::vector<int> &sub);
		static void		initializeToInsert(const std::vector<int> &numbers, std::vector<int> &toInsert);
		static void		insertion(const std::vector<int> &numbers, std::vector<int> &sub);
		static void		binaryInsert(std::vector<int> &sub, size_t start, size_t end, int nb);

// *********************************************************************
// ************************* DEQUE *************************************
// *********************************************************************

		static void		makePairs(std::deque<int> &numbers);
		static void		mergeSort(std::deque<int> &numbers, size_t left, size_t right);
		static void		merge(std::deque<int> &numbers, size_t left, size_t mid, size_t right);
		static void		initializeSubSequence(const std::deque<int> &numbers, std::deque<int> &sub);
		static void		initializeToInsert(const std::deque<int> &numbers, std::deque<int> &toInsert);
		static void		insertion(const std::deque<int> &numbers, std::deque<int> &sub);
		static void		binaryInsert(std::deque<int> &sub, size_t start, size_t end, int nb);
};

template <typename array>
bool	isSorted(array a, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			return (false);
		}
	}
	return (true);
}

template <typename array>
void	printArray(array a, size_t size)
{
	if (size == 0)
		return ;
	for (size_t i = 0; i < size - 1; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << a[size - 1];
}

#endif