#ifndef KDTREE_HPP
#define KDTREE_HPP
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

namespace KDTree{
	struct Node{
		// Index of neighbour struct
		int parent	= -1;
		int left	= -1;
		int right	= -1;
		// Index of point
		int idx		= -1;
		// Split Value
		float value	= -1;
	};

	template<class T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& _list){
	    for(auto item : _list)
	      os << item << " ";
	    return os;
	}

	void
	buildSide(const std::vector<int>& _indexList, const std::vector<float>& _distList){
	    const std::size_t half_size = _indexList.size() / 2;
	    std::vector<int> left(_indexList.begin(), _indexList.begin() + half_size);
	    std::vector<int> right(_indexList.begin() + half_size + 1, _indexList.end());

	    std::cout << _indexList << "\n";

	    std::cout << _indexList[half_size] << "\n";

	    std::cout << left << "\n";
	    std::cout << right << "\n";
	}

	bool
	buildKDTree(const std::vector<std::vector<float>>& _keysList){
		int idx = 0;
		std::vector<int>   indxList(_keysList.size());
		std::vector<float> distanceList(_keysList.size());
		// Calculate Distance and fill idx vector
		for(const auto& key : _keysList){
			float temp = 0;
			for(const auto t : key){
				temp += t * t;
			}
			indxList[idx] = idx;
			distanceList[idx++] = temp;
		}
		// Sort indx Vector
		std::sort(indxList.begin(), indxList.end(), [&](int t1, int t2){
		    return distanceList[t1] < distanceList[t2];
		  });
		std::size_t mid = indxList.size() / 2;
		std::vector<Node> nodesList;
		Node root;
		root.idx = indxList[mid];
		nodesList.push_back(root);

		buildSide(indxList, distanceList);

		return false;
	}

	float
	generateFloat(){
		    static std::random_device rd;
			static std::mt19937 mt(rd());
			static std::uniform_real_distribution<double> dist(0, 10);
			return dist(mt);
	}

	void
	generateList(std::vector<std::vector<float>>& _keysList, int _keysCount, int _dim){
		_keysList.resize(_keysCount);
		for(auto& key : _keysList){
			key.resize(_dim);
			for(auto& item : key)
				item = generateFloat(); 
		}
	}
}
#endif//KDTREE_HPP
