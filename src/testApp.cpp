#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    bg.set(22, 30, 37);
    
    ofSetFullscreen(true);
    
    color.loadImage("colors.jpg");
    
    ofBackground(bg);
    ofSetFrameRate(FRAMES);
    font.loadFont("Archer-SembdItal-Pro.otf", 80, true,true,true);
	
	//phrase = "Text Join Algo to 646 755 7229";
    
    pos.set( ofRandom(20, ofGetWidth() - font.stringWidth(phrase) ) , ofRandom(font.getLineHeight(), ofGetHeight() - font.getLineHeight() ));
	
	//put all the letters of the phrase into 
	//our vector of ofTTF Characters
    //makePhrase(phrase, EXPLODE);
    
    //http.setup();
    
//    world.init();
//    world.setGravity(0, 10 );
//    world.createGround();
//    world.setFPS(30);
//    
    
    selector = BREAKER;
	
		
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    if(phrases.size() < 8){
    
        if( ofGetFrameNum() % FRAMES*2 == 0){ 
            
            //http.checkDB();
            
//            if( http.databaseInfo() == true ){
//            
//            vector <string> result = ofSplitString(http.responseStr, "|");
//            
//            if(result.size() == 3){
//                
//                phraseID = result[0];
//                senderText = result[1];
//                visType = ofToInt(result[2]);
//                
//                
//                makePhrase(senderText, visType);
//                
//                http.sendURL( phraseID );
//                
//                
//            } else{
//                
//                cout << "Result Error, DB Query Returned: " << http.responseStr << endl;
//            }
//        }
            
        }
    }
    
    for (int i = 0; i < phrases.size(); i++) {
            
        if(phrases[i].timer > 35000) {
            
            
            phrases[i].remove();
            phrases.erase(phrases.begin()+i);
            
            cout << "phrases.size: " << phrases.size() << endl;
            
        }else{
        
        
            phrases[i].update();

        }
    
    }

    
}


//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0; i < phrases.size(); i++) {
        phrases[i].draw();
    }
    
    ofDrawBitmapString(phrase, 20, 20);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key != OF_KEY_RETURN && key != OF_KEY_BACKSPACE) {
        
        phrase += key;
        
    } else if( key == OF_KEY_BACKSPACE ){
    
        phrase = phrase.substr(0, phrase.size()-1); 
    
    } else if (key == OF_KEY_RETURN) {
        
        makePhrase(phrase, selector);
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    selector++;
    if(selector > SWIRL) selector = 0;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void testApp::makePhrase(string _p, int _v ){
    
    Phrase temp;
    pos.set( ofRandom(10, ofGetWidth() - font.stringWidth(_p) ) ,ofRandom(font.getLineHeight(), ofGetHeight() - font.getLineHeight() ));
    ofColor c = color.getColor( ofRandom(color.width), 50);
    temp.setup(_p, _v, &font, pos, &bg, c);
    phrases.push_back(temp);
    phrase = "";
    
}