/*
 * engine.h
 *
 *  Created on: 9 Dec 2017
 *      Author: kunson01
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>

class Engine {
	private:
		double size;
	public:
		Engine(double _size): size(_size) { };

		std::string getEngineInfo() {
			// convert double to string
			std::string line = std::to_string(size);
			line = line + "L";
			return line;
		}
};

#endif /* ENGINE_H_ */
