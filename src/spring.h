//
//  spring.h
//  
//
//  Created by Zach Lieberman on Modified by Chris Piuggi 12/5/11.

#ifndef SPRING_H
#define SPRING_H

#include "ofMain.h"

#include "particle.h"

class spring {

	public:

		spring();
		
		particle * particleA;
		particle * particleB;
		
		float distance;
        float originalDist;
		float springiness;	 // this is the k, springiness constant
	
		void update();
		void draw();
	
	
};


#endif