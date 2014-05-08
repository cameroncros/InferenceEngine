/*
 * Engine.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine();
	virtual ~Engine();

	virtual void run()=0;
	virtual void print()=0;

};

#endif /* ENGINE_H_ */
