// Author Sean Davis
#include "router.h"
#include <iostream>

using namespace std;

Router::Router(const Map1000 *map, int width)
{
	widthCopy = width;

    newMap = new Map1000;

    for(int y = width - 1; y >= 0; y--)
    for(int x = 0; x < width; x++)
    {
        newMap->map1000[x][y] = map->map1000[x][y];
    }






/*
    bool known[20] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    int dV[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int pV[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

*/
} // Router()

Router::~Router()
{
	delete[] newMap;
}  // ~Router()


void Router::findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount)
{
/*
	int i = 0;
	for(; i < cityCount; i++)
	{
		int incI = i++;
		int dx = cityPos[incI].x - cityPos[i].x;
		int dy = cityPos[incI].y - cityPos[i].y;
	}
*/
	
	int i = 0;
	int numEdges;
	double incrementX, incrementY;
	for(; i < cityCount; i++)
	{
		int incI = i++;
		int dx = cityPos[incI].x - cityPos[i].x;
		int dy = cityPos[incI].y - cityPos[i].y;

		if(absValue(dx) > absValue(dy))
			numEdges = absValue(dx);
		else
			numEdges = absValue(dy);

		incrementX = dx / (float) numEdges;
		incrementY = dy / (float) numEdges;

		int j = 0, x = 0, y = 0;
		for(; j < numEdges-1; j++)
		{
			x = x + incrementX;
			y = y + incrementY;
			paths[j].startX = roundValue(static_cast<double> (x));
			paths[j].startY = roundValue(static_cast<double> (y));
			paths[j].endX = roundValue(static_cast<double> (x)) + roundValue(static_cast<double> (incrementX));
			paths[j].endY = roundValue(static_cast<double> (y)) + roundValue(static_cast<double> (incrementY));
			pathCount++;
		}


	}

} // findRoutes()

int Router::absValue(int value)
{
	if(value < 0)
		return value * -1;
	else
		return value;
}

long Router::roundValue(double value)
{
	double v = 0.0;
	v = value - (int) value;
	if(v >= 0.5)
		return (int(value + 1));
	else
		return (int(value));
}