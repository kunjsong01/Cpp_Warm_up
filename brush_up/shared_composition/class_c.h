/*
 * class_c.h
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#ifndef CLASS_C_H_
#define CLASS_C_H_

using namespace std;

class C {
	public:
		int store;
		C(int _store): store(_store) {

		}

		void getStore() {
			cout << store << endl;
		}
};



#endif /* CLASS_C_H_ */
