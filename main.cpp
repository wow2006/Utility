#include "timer.hpp"
#include "kdtree.hpp"

int
main(int argc, char* argv[]){
	std::vector<std::vector<float>> keysList;
	utility::Timer time;
	KDTree::generateList(keysList, 10, 3);
	time.end("Generate");
	time.reset();
	KDTree::buildKDTree(keysList);
	time.end("Build Tree");
	return 0;
}

