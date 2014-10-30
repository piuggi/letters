#pragma once

#define FRAMES 30

#define AGE 0
#define EXPLODE 1
#define BREAKER 2
#define MOVE 3
#define SWIRL 4

#include "ofMain.h"
//#include "ofxBox2d.h"
#include "phrase.h"
//#include "http.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void makePhrase(string _p, int _v);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofTrueTypeFont font;
        ofPoint pos;
        string phrase;
        
        ofColor bg;

        vector <Phrase> phrases;
        
    int selector;
    
        ofImage color;
    
        //ofxBox2d world;
        
    
        //databases stuff
        //HTTPConnect http;
        string phraseID, senderText;
        int visType;
        //void prepNSend();





};
