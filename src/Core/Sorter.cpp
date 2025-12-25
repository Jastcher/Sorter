#include "Sorter.h"
#include "Core/Sounds.h"
#include <memory>
#include <iostream>

namespace Template
{

Sorter::Sorter(std::shared_ptr<SoundEngine> _soundEngine) : soundEngine(_soundEngine)
{
	ResizeData();
	sortTh = std::thread(&Sorter::Sort, this);

	GetSorters();

	sorterNames.reserve(sorters.size());
	for(const auto& it : sorters) { sorterNames.push_back(it.first.c_str()); }
}
Sorter::~Sorter()
{
}

void Sorter::ResizeData()
{
	data.reserve(dataSize);
	data.resize(dataSize);

	for(int i = 0; i < dataSize; i++) { data[i] = i + 1; }
	color = green;
}

void Sorter::Sort()
{
	while(true)
	{
		if(!start) { continue; }

		soundEngine->Play();

		sorters[sorterNames[sorterSelected]](props);

		soundEngine->Stop();

		if(IsSorted()) color = green;

		start = false;
		props.stop = false;
	}
}

void Sorter::ShuffleData()
{
	std::shuffle(std::begin(data), std::end(data), rng);
	color = red;
}

bool Sorter::IsSorted()
{
	for(unsigned int i = 0; i < dataSize; i++)
	{
		if(data[i] != i + 1) return 0;
	}

	return 1;
}
} // namespace Template
