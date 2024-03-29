//
//  particle.h
//  
//
//  Created by Zach Lieberman on Modified by Chris Piuggi 12/5/11.


#pragma once

#include "ofMain.h"

class flockingForce {
public:
	
	int			count;
	ofVec2f	sum;
	float		distance;
	float		strength;
	
};

class particle
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
        
        void addClockwiseForce(particle &p, float radius, float scale);
        void addCounterClockwiseForce(particle &p, float radius, float scale);
    
		void addDampingForce();
        
        void addForFlocking(particle &p);
        void addFlockingForce();
        
        flockingForce cohesion;
        flockingForce seperation;
        flockingForce alignment;
        
        
		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw(bool fill, ofColor *color);
	
		void bounceOffWalls();
	
	
		float damping;

    protected:
    private:
};

