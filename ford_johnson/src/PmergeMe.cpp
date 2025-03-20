#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(const PmergeMe &otherPmergeMe)
{
	if (this != &otherPmergeMe)
	{
		*this = otherPmergeMe;
	}
	return;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &otherPmergeMe)
{
	if (this != &otherPmergeMe)
	{
	}		
	return(*this);
}

size_t	PmergeMe::jacobsthalIndex(size_t index)
{
	if (index == 0)
		return (0);
	else if (index == 1)
		return (1);
	else
	{
		return (jacobsthalIndex(index - 1) + 2 * jacobsthalIndex(index - 2));
	}
}

// *********************************************************************
// ************************* VECTOR ************************************
// *********************************************************************

void	PmergeMe::makePairs(std::vector<int> &numbers)
{
	for (size_t i = 0; i < numbers.size() - 1; i += 2)
	{
		if (numbers[i] > numbers[i + 1])
		{
			std::swap(numbers[i], numbers[i + 1]);
		}
	}
}

void	PmergeMe::merge(std::vector<int> &numbers, size_t left, size_t mid, size_t right)
{
	size_t	leftSize = mid - left + 2;
	size_t	rightSize = right - mid;

	std::vector<int>	leftVect(numbers.begin() + left, numbers.begin() + left + leftSize);
	std::vector<int>	rightVect(numbers.begin() + mid + 2, numbers.begin() + mid + 2 + rightSize);
	
	size_t i = 0;
	size_t j = 0;
	for (size_t k = left; k < right + 1; k += 2)	
	{
		if (i < leftSize && (j >= rightSize || leftVect[i + 1] < rightVect[j + 1]))
		{
			numbers[k] = leftVect[i];
			numbers[k + 1] = leftVect[i + 1];
			i += 2;
		}
		else
		{
			numbers[k] = rightVect[j];
			numbers[k + 1] = rightVect[j + 1];
			j += 2;
		}
	}
}

void	PmergeMe::mergeSort(std::vector<int> &numbers, size_t begin, size_t end)
{
	if (begin >= end)
	{
		return ;
	}
	size_t mid = begin + (end - begin) / 2;
	mergeSort(numbers, begin, mid);
	mergeSort(numbers, mid + 1, end);
	merge(numbers, begin * 2, mid * 2, end * 2);
}

void PmergeMe::initializeSubSequence(const std::vector<int> &numbers, std::vector<int> &sub)
{
	sub.reserve(numbers.size());
	for (size_t i = 1; i < numbers.size() ; i += 2)
	{
		sub.push_back(numbers[i]);
	}
}

void	PmergeMe::initializeToInsert(const std::vector<int> &numbers, std::vector<int> &toInsert)
{
	toInsert.reserve(numbers.size() / 2);
	for (size_t i = 0; i < numbers.size(); i += 2)
	{
		toInsert.push_back(numbers[i]);
	}
}

void	PmergeMe::binaryInsert(std::vector<int> &sub, size_t start, size_t end, int nb)
{
	size_t	mid = (start + end) / 2;

	if (start == end)
	{
		if (nb < sub[start])
		{
			sub.insert(sub.begin() + start, nb);
		}
		else
		{
			sub.insert(sub.begin() + start + 1, nb);
		}
		return ;
	}
	if (nb < sub[mid])
	{
		return (binaryInsert(sub, start, mid, nb));
	}
	else
	{
		return (binaryInsert(sub, mid + 1, end, nb));
	}
}

void	PmergeMe::insertion(const std::vector<int> &toInsert, std::vector<int> &sub)
{
	size_t	insertCounter = 1;
	size_t	i = 0;
	size_t	jacobIndex = 1;
	int		distanceForward;
	size_t	start;

	while (true)
	{
		distanceForward = 2 * jacobsthalIndex(jacobIndex);
		if (i + distanceForward >= toInsert.size())
			break ;
		start = i;
		i += distanceForward;
		while (i > start)
		{
			binaryInsert(sub, 0, i + insertCounter - 1, toInsert[i]);
			++insertCounter;
			--i;
		}
		i += distanceForward;
		++jacobIndex;
	}
	start = i;
	i = toInsert.size() - 1;
	while (i > start)
	{
		binaryInsert(sub, 0, sub.size() - 1, toInsert[i]);
		--i;
	}
}

void	PmergeMe::sort(std::vector<int> &numbers)
{
	std::vector<int>	subSequence;
	std::vector<int>	toInsert;
	
	makePairs(numbers);
	if (numbers.size() % 2 == 0)
		mergeSort(numbers, 0, (numbers.size() - 1) / 2);
	else
		mergeSort(numbers, 0, (numbers.size() - 1) / 2 - 1);
	initializeSubSequence(numbers, subSequence);
	initializeToInsert(numbers, toInsert);
	subSequence.insert(subSequence.begin(), toInsert[0]);
	insertion(toInsert, subSequence);
	numbers = subSequence;
}

// *********************************************************************
// ************************* DEQUE *************************************
// *********************************************************************

void	PmergeMe::makePairs(std::deque<int> &numbers)
{
	for (size_t i = 0; i < numbers.size() - 1; i += 2)
	{
		if (numbers[i] > numbers[i + 1])
		{
			std::swap(numbers[i], numbers[i + 1]);
		}
	}
}

void	PmergeMe::merge(std::deque<int> &numbers, size_t left, size_t mid, size_t right)
{
	size_t	leftSize = mid - left + 2;
	size_t	rightSize = right - mid;

	std::deque<int>	leftVect(numbers.begin() + left, numbers.begin() + left + leftSize);
	std::deque<int>	rightVect(numbers.begin() + mid + 2, numbers.begin() + mid + 2 + rightSize);
	
	size_t i = 0;
	size_t j = 0;
	for (size_t k = left; k < right + 1; k += 2)	
	{
		if (i < leftSize && (j >= rightSize || leftVect[i + 1] < rightVect[j + 1]))
		{
			numbers[k] = leftVect[i];
			numbers[k + 1] = leftVect[i + 1];
			i += 2;
		}
		else
		{
			numbers[k] = rightVect[j];
			numbers[k + 1] = rightVect[j + 1];
			j += 2;
		}
	}
}

void	PmergeMe::mergeSort(std::deque<int> &numbers, size_t begin, size_t end)
{
	if (begin >= end)
	{
		return ;
	}
	size_t mid = begin + (end - begin) / 2;
	mergeSort(numbers, begin, mid);
	mergeSort(numbers, mid + 1, end);
	merge(numbers, begin * 2, mid * 2, end * 2);
}

void PmergeMe::initializeSubSequence(const std::deque<int> &numbers, std::deque<int> &sub)
{
	for (size_t i = 1; i < numbers.size() ; i += 2)
	{
		sub.push_back(numbers[i]);
	}
}

void	PmergeMe::initializeToInsert(const std::deque<int> &numbers, std::deque<int> &toInsert)
{
	for (size_t i = 0; i < numbers.size(); i += 2)
	{
		toInsert.push_back(numbers[i]);
	}
}

void	PmergeMe::binaryInsert(std::deque<int> &sub, size_t start, size_t end, int nb)
{
	size_t	mid = (start + end) / 2;

	if (start == end)
	{
		if (nb < sub[start])
		{
			sub.insert(sub.begin() + start, nb);
		}
		else
		{
			sub.insert(sub.begin() + start + 1, nb);
		}
		return ;
	}
	if (nb < sub[mid])
	{
		return (binaryInsert(sub, start, mid, nb));
	}
	else
	{
		return (binaryInsert(sub, mid + 1, end, nb));
	}
}

void	PmergeMe::insertion(const std::deque<int> &toInsert, std::deque<int> &sub)
{
	size_t	insertCounter = 1;
	size_t	i = 0;
	size_t	jacobIndex = 1;
	int		distanceForward;
	size_t	start;

	while (true)
	{
		distanceForward = 2 * jacobsthalIndex(jacobIndex);
		if (i + distanceForward >= toInsert.size())
			break ;
		start = i;
		i += distanceForward;
		while (i > start)
		{
			binaryInsert(sub, 0, i + insertCounter - 1, toInsert[i]);
			++insertCounter;
			--i;
		}
		i += distanceForward;
		++jacobIndex;
	}
	start = i;
	i = toInsert.size() - 1;
	while (i > start)
	{
		binaryInsert(sub, 0, sub.size() - 1, toInsert[i]);
		--i;
	}
}

void	PmergeMe::sort(std::deque<int> &numbers)
{
	std::deque<int>	subSequence;
	std::deque<int>	toInsert;
	
	makePairs(numbers);
	if (numbers.size() % 2 == 0)
		mergeSort(numbers, 0, (numbers.size() - 1) / 2);
	else
		mergeSort(numbers, 0, (numbers.size() - 1) / 2 - 1);
	initializeSubSequence(numbers, subSequence);
	initializeToInsert(numbers, toInsert);
	subSequence.insert(subSequence.begin(), toInsert[0]);
	insertion(toInsert, subSequence);
	numbers = subSequence;
}