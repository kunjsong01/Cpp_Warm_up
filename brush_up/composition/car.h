/*
 * car.h
 *
 *  Created on: 9 Dec 2017
 *      Author: kunson01
 */

#ifndef CAR_H_
#define CAR_H_

#include <string>
#include <iostream>
#include "engine.h"

class Car {
	private:
		std::string make;
		int year;
		Engine engine;
	public:
		Car(std::string _make, int _year, Engine _engine): make(_make), year(_year), engine(_engine) {};

		void getCarInfo() {
			std::cout << "Car " << make << " manufactured in " << year << ", has an engine: " << engine.getEngineInfo() << std::endl;
		}
};

#endif /* CAR_H_ */
