// Author: Sean Davis

#ifndef ROUTER_H
  #define ROUTER_H

#include "RouterRunner.h"

class Router
{
public:
  Router(const Map1000 *map, int width);
  int widthCopy;
  ~Router();
  void findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount);
  int absValue(int value);
  long roundValue(double value);
private:
	Map1000 *newMap;
};


#endif
