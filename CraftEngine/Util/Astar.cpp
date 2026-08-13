#include "Astar.h"
#include <cmath>
#include <set>
#include <stack>

using cCoord = std::pair<double, std::pair<int, int>>;

Astar::Astar(std::vector<std::vector<int>> map, const Vector2& startPosition, const Vector2& destination)
	:map(map), startPosition(startPosition), destination(destination)
{
	if (this->map.empty())
	{
		return;
	}
	ROW = map.size();
	COL = map[0].size();
}

std::vector<Vector2> Astar::AstarFinder(std::vector<std::vector<int>>& map, const Vector2& startPosition, const Vector2& destination)
{
	std::vector<Vector2> nullVector;
	if (!IsInRange(startPosition.x, startPosition.y)
		|| !IsInRange(destination.x, destination.y)) { return nullVector;}

	if (!IsUnblocked(map, startPosition.x, startPosition.y)
		|| !IsUnblocked(map, destination.x, destination.y)) { return nullVector; }

	if (IsDestination(startPosition.x, startPosition.y, destination)) { return nullVector; }
	
	std::vector<std::vector<bool>> closedList(
		map[0].size(),
		std::vector<bool>(map.size(), false) // (size, 초기값)
	);

	Node baseNode; //초기값
	baseNode.parentx = -1;
	baseNode.parenty = -1;
	baseNode.f = INF;
	baseNode.g = INF;
	baseNode.h = INF;
	std::vector<std::vector<Node>> node(
		map[0].size(),
		std::vector<Node>(map.size(), baseNode)
	);
	node[startPosition.x][startPosition.y].f = 0.0;
	node[startPosition.x][startPosition.y].g = 0.0;
	node[startPosition.x][startPosition.y].h = 0.0;
	node[startPosition.x][startPosition.y].parentx = startPosition.x;
	node[startPosition.x][startPosition.y].parenty = startPosition.y;

	std::set<cCoord> openList;
	openList.insert({ 0.0, {startPosition.x, startPosition.y} });
	
	while (!openList.empty())
	{
		cCoord cc = *openList.begin();
		openList.erase(openList.begin());

		int x = cc.second.first;
		int y = cc.second.second;

		closedList[x][y] = true;

		double nf, ng, nh;

		for (int ix = 0; ix < 4; ++ix)
		{
			int nx = x + dx1[ix];
			int ny = y + dy1[ix];

			if (IsInRange(nx, ny))
			{
				if (IsDestination(nx, ny, destination))
				{
					node[nx][ny].parentx = x;
					node[nx][ny].parenty = y;
					return TracePath(node, destination);
				}

				// bfs와 굳이 비교하자면, closedList를 방문여부라고 생각하시면 됩니다.
				else if (!closedList[nx][ny] && IsUnblocked(map, nx, ny))
				{
					// 이부분 y x, ny nx 헷갈리는거 조심
					ng = node[x][y].g + 1.0;
					nh = CalcHValue(nx, ny, destination);
					nf = ng + nh;

					// 만약 한번도 갱신이 안된f거나, 새로갱신될 f가 기존f보다 작을시 참
					if (node[nx][ny].f == INF || node[nx][ny].f > nf)
					{
						node[nx][ny].f = nf;
						node[nx][ny].g = ng;
						node[nx][ny].h = nh;
						node[nx][ny].parentx = x;
						node[nx][ny].parenty = y;
						openList.insert({ nf, { nx, ny } });
					}
				}
			}
		}
		//대각
		for (int i = 0; i < 4; ++i) 
		{
			int nx = x + dx2[i];
			int ny = y + dy2[i];

			if (IsInRange(nx, ny)) 
			{
				if (IsDestination(nx, ny, destination)) 
				{
					node[nx][ny].parentx = x;
					node[nx][ny].parenty = y;
					return TracePath(node, destination);
				}
				else if (!closedList[nx][ny] && IsUnblocked(map, nx, ny)) 
				{
					ng = node[x][y].g + 1.414; //대각 처리
					nh = CalcHValue(nx, ny, destination);
					nf = ng + nh;

					if (node[nx][ny].f == INF || node[nx][ny].f > nf)
					{
						node[nx][ny].f = nf;
						node[nx][ny].g = ng;
						node[nx][ny].h = nh;
						node[nx][ny].parentx = x;
						node[nx][ny].parenty = y;
						openList.insert({ nf, { nx, ny } });
					}
				}
			}

		}
	}
	return nullVector;
}
// 목적지 확인
bool Astar::IsDestination(int x, int y, const Vector2& destination)
{
	return (x == destination.x && y == destination.y );
}
//유효한 좌표인지
bool Astar::IsInRange(int x, int y)
{
	return (x >= 0 && x < COL && y >= 0 && y < ROW);
}
//벽이 있는지
bool Astar::IsUnblocked(std::vector<std::vector<int>>& map, int x, int y)
{
	return (map[y][x] == 0);
}

double Astar::CalcHValue(int x, int y, const Vector2& destination)
{
	return static_cast<double>(
		std::sqrt(
			std::pow(x - destination.x, 2)
			+ std::pow(y - destination.y, 2)
		));
}

std::vector<Vector2> Astar::TracePath(
	const std::vector<std::vector<Node>>& node,
	const Vector2& destination)
{
	std::vector<Vector2> moveDirection;

	int x = destination.x;
	int y = destination.y;

	while (!(node[x][y].parentx == x &&
		node[x][y].parenty == y))
	{
		int tempX = node[x][y].parentx;
		int tempY = node[x][y].parenty;

		moveDirection.emplace_back(x - node[x][y].parentx, y - node[x][y].parenty);

		x = tempX;
		y = tempY;
	}

	return moveDirection;
}
