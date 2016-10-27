#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <vector>
#include <typeinfo>

//override default begin, end functions - needed for C++11 foreach loop with dynamically allocated double array
namespace std 
{
	template <typename T> T* begin(std::pair<T*, T*> const& p)
	{
		return p.first;
	}
	template <typename T> T* end(std::pair<T*, T*> const& p)
	{
		return p.second;
	}
}

template <typename T>struct wrapped_array 
{
	wrapped_array(T* first, T* last) : begin_{ first }, end_{ last } {}
	wrapped_array(T* first, std::ptrdiff_t size): wrapped_array{ first, first + size } {}

	T*  begin() const noexcept { return begin_; }
	T*  end() const noexcept { return end_; }

	T* begin_;
	T* end_;
};

template <typename T>wrapped_array<T> wrap_array(T* first, std::ptrdiff_t size) noexcept
{
	return{ first, size };
}


int main()
{
	size_t arrSize = 20000000;


	std::vector<double> arr2(arrSize);
	std::fill(arr2.begin(), arr2.end(), 0.0);
	auto start = clock(), stop = clock();

	std::cout << "test on "<< typeid(arr2).name() << " size: " << arrSize<<std::endl;
	

	//normal for loop

	start = clock();
	for (size_t i = 1; i<arrSize; i++)
		arr2[i] += 1;
	stop = clock();
	std::cout<< std::setprecision(20) << "for loop: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

	
	//C++11 for each loop

	start = clock();
	for(double i:arr2)
		i += 1;
	stop = clock();
	std::cout << std::setprecision(20) << "c++11 foreach (range) loop: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) <<std::endl;


	//STL for_each

	start = clock();
	std::for_each(arr2.begin(), arr2.end(), [](double element) {element += 1; });
	stop = clock();
	std::cout << std::setprecision(20) << "stl for_each loop: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

	//-------------------------------------------------------


	std::cout << "test on double*" << " size: " << arrSize<<std::endl;


	double* array = new double[arrSize];	

	for (size_t i = 1; i < arrSize; i++)
		array[i] = 0;



	//normal for loop
	start = clock();
	for (size_t i = 1; i<arrSize; i++)
	array[i] += 1;
	stop = clock();
	std::cout<< std::setprecision(20) << "for loop: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;


	//C++11 for each loop

	//wrapper:
	start = clock();
	for (auto&& i : wrap_array(array, arrSize))
	stop = clock();
	std::cout << std::setprecision(20) << "c++11 foreach (range) loop - wrapper: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

	//pair:
	start = clock();
	for (auto&& i : wrap_array(array, arrSize))
		stop = clock();
	std::cout << std::setprecision(20) << "c++11 foreach (range) loop - pair: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

	for (auto&& i : std::make_pair(array, array + arrSize))




	//STL for_each
	start = clock();
	std::for_each(array, array + arrSize, [](double element) {element +=1; });
	stop = clock();
	std::cout << std::setprecision(20) << "stl for_each loop: " << (stop - start) / static_cast<double>(CLOCKS_PER_SEC) <<std::endl;

	
	delete[] array;
	system("pause");
	return 0;
}


