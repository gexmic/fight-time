#pragma once
#include <vector>

namespace GEX
{
	class Map
	{
	public:
		Map();
		~Map();

		void draw();

	private:
		std::vector<int> dessertMap;
	};
}

