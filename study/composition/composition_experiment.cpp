// cconst / non-const object behaviour
// const / non-const method behaviour

#include <iostream>
#include <string>

#include "car.h"
#include "engine.h"
using namespace std;

int main() {

	Engine small(1.2);
	Engine large(6.5);

	Car hatchback("Renault", 1998, small);
	Car crossover("Jeep", 2010, large);

	hatchback.getCarInfo();
	crossover.getCarInfo();
}
