#pragma once

#include <memory>
#include <random>
#include <thread>
#include <vector>
#include <functional>
#include <algorithm>
#include "glm/glm.hpp"
#include <map>

#include "Sounds.h"

namespace Template
{
struct SorterProps
{
  std::vector<int> &data;
  int ind1;
  int ind2;
  int sleep;
  bool stop;
};

class Sorter
{

public:
  Sorter(std::shared_ptr<SoundEngine> _soundEngine);
  ~Sorter();

  void ResizeData();
  void ShuffleData();
  void Sort();
  bool IsSorted();

  unsigned int dataSize = 10000;

  std::vector<int> data;

  std::random_device rd          = std::random_device{};
  std::default_random_engine rng = std::default_random_engine{rd()};

  std::vector<const char *> sorterNames;

  int sorterSelected = 0;

  SorterProps props{data, 0, 0, 0, false};

  glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

  std::thread sortTh;
  bool start = false;

private:
  std::map<std::string, std::function<void(SorterProps &)>> sorters;
  void GetSorters();

  glm::vec3 red   = glm::vec3(1.0f, 0.0f, 0.0f);
  glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 blue  = glm::vec3(0.0f, 0.0f, 1.0f);

  std::shared_ptr<SoundEngine> soundEngine;
};

} // namespace Template
