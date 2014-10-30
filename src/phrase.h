//
//  phrase.h
//  letters
//
//  Created by Chris Piuggi on 12/5/11.
//  Copyright (c) 2011. All rights reserved.
//

#pragma once
#include "ofMain.h"
//#include "ofxBox2d.h"
#include "particle.h"
#include "spring.h"

#define PARTICLE_NUM 15

#define AGE 0
#define EXPLODE 1
#define BREAKER 2
#define MOVE 3
#define SWIRL 4

class Phrase {
  
    public:
        Phrase();
    
        void setup(string _phrase, int _visual, ofTrueTypeFont * _font, ofPoint _pos, ofColor * _bg, ofColor _c);
        virtual void update();
        virtual void draw();
        void remove();
        void updatePos(Phrase *_p);
    
        ofTrueTypeFont *font;
        vector <ofTTFCharacter> character;
        ofPoint pos;
        string phrase; 
        int animation;
        ofColor *bg; 
        ofColor color;
    
        float totalLength;
        float timer;
        //ofxBox2d *world;
        
        
    private:
        
        void makeParticles();
        void makeSprings();
        void setupCharacters(int _a);
        void drawCharactersAs(bool fill);
        void drawParticlesAs(bool fill);

        string ofChartoString(char c);    
        void updateExplode();
        void updateAge();
        void updateBreak();
        void updateFlock();
        void updateSwirl();
        
    
    
        vector <ofRectangle> letterBox;
        vector <char> letter;
        vector <ofPolyline>	resamples;        
        vector <ofPolyline> lines;
        //vector <ofxBox2dPolygon> polygon;
        
        //temp to see if this all works, will be vec of particles.
        vector <particle *> particles; 
        vector<spring> springs;
        
        float spacing;
        bool bTwoShapes;
        int index, posCount;
        float start;    
        
        //string _explode, _break, _age;
        


};
