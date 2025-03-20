# include "PmergeMe.hpp"

std::vector<int> initVect(int ac, char **av)
{
	long long			nb;
	std::vector<int>	numbers;
	std::string			str;


	numbers.reserve(ac - 1);
	for (int i = 1; i < ac; i++)
	{
		str = av[i];
		nb = std::strtol(av[i], NULL, 10);
		if (nb < 0 || str.find_first_not_of("0123456789", 0) != std::string::npos
			|| errno == ERANGE || nb > std::numeric_limits<int>::max())
		{
			throw std::invalid_argument("Invalid number");
		}
		numbers.push_back(nb);
	}
	return (numbers);
}

std::deque<int> initDeque(std::vector<int> numbersVect)
{
	std::deque<int>	numbersDeque(numbersVect.begin(), numbersVect.end());

	return (numbersDeque);
}

int	main(int ac, char **av)
{
	std::vector<int> numbersVec;
	std::deque<int> numbersDeque;
	clock_t			start;
	clock_t			end;

	try
	{
		start = std::clock();
		numbersVec = initVect(ac, av);
		std::cout << "Before : ";
		printArray(numbersVec, numbersVec.size());
		PmergeMe::sort(numbersVec);
		end = std::clock();
		std::cout << std::endl << "After : ";
		printArray(numbersVec, numbersVec.size());
		std::cout << std::endl << "Time to process a range of " << numbersVec.size()
			<< " elements with std::vector : " << double(end - start) / double(CLOCKS_PER_SEC) * 1000000 << " us" << std::endl;
		start = std::clock();
		numbersDeque = initDeque(numbersVec);
		PmergeMe::sort(numbersDeque);
		end = std::clock();
		std::cout << "Time to process a range of " << numbersDeque.size()
			<< " elements with std::deque : " << double(end - start) / double(CLOCKS_PER_SEC) * 1000000 << " us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error" << std::endl;
	}	
	return (0);
}