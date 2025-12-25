#include "Sorter.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

namespace Template
{

static inline bool Routine(const SorterProps& props)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(props.sleep));
	return props.stop;
}

void Sorter::GetSorters()
{
	sorters["Selection"] = [](SorterProps& props)
	{
		int& i = props.ind1;
		int& j = props.ind2;
		for(i = 0; i < props.data.size(); i++)
		{

			unsigned int minIndex = i;
			for(j = i + 1; j < props.data.size(); j++)
			{
				if(props.data[j] < props.data[minIndex]) minIndex = j;
			}

			std::swap(props.data[i], props.data[minIndex]);

			if(Routine(props)) return;
		}
	};

	sorters["Bubble"] = [](SorterProps& props)
	{
		int& i = props.ind1;
		int& j = props.ind2;

		for(i = 0; i < props.data.size(); i++)
		{
			for(j = 0; j < props.data.size() - 1; j++)
			{
				if(props.data[j] > props.data[j + 1]) { std::swap(props.data[j], props.data[j + 1]); }

				if(Routine(props)) return;
			}
		}
	};

	sorters["Insertion"] = [](SorterProps& props)
	{
		int& i = props.ind1;
		int& j = props.ind2;

		for(i = 1; i < props.data.size(); i++)
		{

			for(j = 0; j < i; j++)
			{
				if(props.data[i] < props.data[j])
				{
					props.data.insert(props.data.begin() + j, props.data[i]);
					props.data.erase(props.data.begin() + i + 1);
				}

				if(Routine(props)) return;
			}
		}
	};
}

} // namespace Template
