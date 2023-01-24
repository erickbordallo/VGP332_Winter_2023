#include "Precompiled.h"
#include "BFS.h"

using namespace AI;


bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	//Reset everything
	graph.ResetSearchParameters();
	mOpenList.clear();
	mClosedList.clear();

	//add the start node to the open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;

	while (!mOpenList.empty() && !found)
	{
		auto currentNode = mOpenList.front();
		mOpenList.pop_front();
		if (currentNode->row == endY && currentNode->column == endX)
		{
			found = true;
		}
		else
		{
			for (auto neighbor : currentNode->neighbors)
			{
				if (neighbor != nullptr && !neighbor->opened && !neighbor->closed)
				{
					neighbor->parent = currentNode;
					neighbor->opened = true;
					//Need to put inside the open list
				}
			}
		}
		currentNode->closed = true;
		mClosedList.push_back(currentNode);
	}

	return found;
	//TODO
	//		while end node not reached && open list isn't empty:
	//			select node N from open list ----> Depend on your startegy
	//			if node is end
	//				found = true
	//			else expand node N :
	//				if expanded node isn't in open list nor closed list
	//					add expanded node to open list, set parent
	//			Add node N to closed list
}