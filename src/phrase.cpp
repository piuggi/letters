//
//  phrase.cpp
//  letters
//
//  Created by Chris Piuggi on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "phrase.h"

//------------------------------------------------------------------------------------

bool comparitor(particle *a, particle *b){
    
    return a->pos.x < b->pos.x; 
}

Phrase::Phrase() {
    
    // this needs to get fixed for %, B Q(for some fonts)
    // needs to be figured out

    
}

//-------------------------------------------------------------------------------------

void Phrase:: remove() {
    
    cout << "attempting to remove" << endl;
    
//    letter.clear();
//    character.clear();
//    letterBox.clear();
//    resamples.clear();
//    lines.clear();
    
    if(animation == EXPLODE || animation == MOVE || animation == SWIRL) {
        
        //clearing the pointers inside an object
        vector <particle *> :: iterator i;
        for (i = particles.begin(); i != particles.end(); i++) {
            delete (*i);
        }
        
        particles.clear();
        
    }
    
}


//-------------------------------------------------------------------------------------

void Phrase::setup(string _phrase, int _visual, ofTrueTypeFont * _font , ofPoint _pos, ofColor * _bg, ofColor _c) {
    
    font =_font;
	phrase = _phrase;
    pos = _pos;
    bg =_bg;
    color = _c;
    color.a = 255;
    animation = _visual;
    //world = _w;
    
    //pos.z = phrase.size() * 15;
    
    
    
    cout << "Animation Type: " << animation << endl;
    
    //cout<< "String Compare == " << animation.compare(_explode) << endl;
    
    setupCharacters(animation);

    
    switch(animation){
            
        case AGE:
                break;
        
        case EXPLODE:
                makeParticles();
                break;
        
        
        case BREAKER:
                makeSprings();
                break;
            
        case MOVE:
            makeParticles();
            break;
            
        case SWIRL:
            makeParticles();
            break;
    
        
    } 
    
    start = ofGetElapsedTimeMillis();

    
}

void Phrase::makeSprings(){
    
    int totalCount = 0;
    for(int i = 0; i< lines.size(); i++){
        
        int counter = 0;
        
        for(int j = 0; j< lines[i].getVertices().size(); j++){
            
            float x = lines[i].getVertices()[j].x;
            float y = lines[i].getVertices()[j].y;
            
            particle * p = new particle();
            p->setInitialCondition(x, y, 0, 0);
            particles.push_back(p);
            counter++;
            
        }
        
        int tempCount = totalCount+counter;
        for (int j = totalCount; j<tempCount; j++) {
            
            spring s;

            s.springiness = 0.52f;
            if(j == tempCount-1){
            s.originalDist = ofDist(particles[j]->pos.x, particles[j]->pos.y, particles[totalCount]->pos.x, particles[totalCount]->pos.y);
            s.distance = s.originalDist;
            s.particleA = particles[j];
            s.particleB = particles[totalCount];     
            }else{
                s.originalDist = ofDist(particles[j]->pos.x, particles[j]->pos.y, particles[j+1]->pos.x, particles[j+1]->pos.y);
                s.distance = s.originalDist;
                s.particleA = particles[j];
                s.particleB = particles[j+1];
            }
            springs.push_back(s);
                    
        }
        
        totalCount += counter;
        
    }
     
}

//--------------------------------------------------------------

void Phrase::setupCharacters(int _a){

    cout <<"phrase: " << phrase.size() << endl;
	spacing = 0;
	for (int i = 0; i < phrase.size(); i++) {
		
		//get the each letter 
		char l = phrase.at(i);
        if(l == ' ') l='_';
        if(l == '%') l='_';
        if(l == 'Q') l='q';
        if(l == 'B') l='b';
        
        letter.push_back(l);
        
        ofRectangle bounding = font->getStringBoundingBox(ofChartoString(letter[i]),0,0);
        
        float tempSpace;
        float kearning = 10;
        
        if (i > 0){
            tempSpace = letterBox[i-1].width +kearning;
        }else {
            spacing = pos.x;
            tempSpace = 0;
        }
        
        spacing +=  tempSpace;
        
        bounding.x += spacing;
        bounding.y += pos.y;
        
        letterBox.push_back(bounding);
        
        ofTTFCharacter temp = font->getCharacterAsPoints(letter[i]);
        character.push_back(temp);
        
        ofPolyline polyline;
        lines.push_back(polyline);
        
        //if character has two lines
        if (character[i].getOutline().size()>1) {
            
            cout << "character " << letter[i] << " has " << character[i].getOutline().size() << " lines." << endl;   
            lines.push_back(polyline);
            
        } 
        
		
	}
	
	cout << "character: "<< character.size() << "  \tlines: "<< lines.size() << endl;
	
    index = 0;
    bTwoShapes = false;
	
    
    //each character check if it has an inside
    //get it outlines and push the vertex into a polyline
	for (int j = 0; j < character.size(); j++) {
        
        float tempSpace;
        float kearning = 10;
        
        if (j > 0){
            tempSpace = letterBox[j-1].width +kearning;
        }else {
            spacing = pos.x;
            tempSpace = 0;
        }
        
        spacing +=  tempSpace;
        
        if(j == character.size()-1){
            
            
            totalLength = spacing + letterBox[j].width; 
            cout << "Total Length " << totalLength << endl;
            
        }
        
		for(int k = 0; k < /*1*/(int)character[j].getOutline().size(); k++){
			
			if( k!= 0) bTwoShapes = true;
            else bTwoShapes = false;
            
            if(k!=0)ofNextContour(true);
            
			for(int i = 0; i < (int)character[j].getOutline()[k].size(); i++){
				
				ofPoint point;
				point.x = character[j].getOutline()[k].getVertices()[i].x + spacing;
				point.y = character[j].getOutline()[k].getVertices()[i].y + pos.y;
				
				if (!bTwoShapes) lines[j+index].addVertex(point);
                else lines[j+index+1].addVertex(point);
                
				
				if(i == (int)character[j].getOutline()[k].size()-1){
                    
					cout << "End of line"<<"\tcharacter: "<< j <<"\toutline:"<< k <<  endl;
                    
					point.x = character[j].getOutline()[k].getVertices()[0].x + spacing;
					point.y = character[j].getOutline()[k].getVertices()[0].y + pos.y;
                    
                    if (!bTwoShapes) lines[j+index].addVertex(point);
                    else lines[j+index+1].addVertex(point);
                    
                    point.x = character[j].getOutline()[k].getVertices()[i].x + spacing;
					point.y = character[j].getOutline()[k].getVertices()[i].y + pos.y;
                    
                    if (!bTwoShapes) lines[j+index].addVertex(point);
                    else lines[j+index+1].addVertex(point);
				}
				
			}
            
            if(bTwoShapes) index++;
            
		}
	}
	
	//resample all lines 
	for (int i = 0; i < lines.size(); i ++) {
		
        
        if(_a== BREAKER){
		ofPolyline lineResampled = lines[i].getResampledBySpacing(15);
		resamples.push_back(lineResampled);
        resamples[i].setClosed(true);
        resamples[i].getSmoothed(8);
        } else {
            
            ofPolyline lineResampled = lines[i].getResampledBySpacing(4);
            resamples.push_back(lineResampled);
            resamples[i].setClosed(true);
            resamples[i].getSmoothed(8);
            
        }
	}

}

//--------------------------------------------------------------

void Phrase::makeParticles(){
    
    index = 0;
    bTwoShapes = false;
    //pos.x -= font->stringWidth(phrase)/6;
    
    for(int j = 0; j< character.size(); j++) {
        
        if (character[j].getOutline().size() > 1) bTwoShapes = true;
        else bTwoShapes = false;
        
        float tempSpace;
        float kearning = 10;
        
        if (j > 0){
            tempSpace = letterBox[j-1].width +kearning;
        }else {
            spacing = pos.x;
            tempSpace = 0;
        }
        
        spacing +=  tempSpace;
        posCount = 0;
        
        if(letter[j] != '_'){
        
            //check all the pixels in the box of the letter
            for(int x = letterBox[j].x; x < (int)letterBox[j].x+letterBox[j].width ; x++ ){
                for(int y = letterBox[j].y ; y < (int)letterBox[j].y+letterBox[j].height ; y++){
                    
                    if(bTwoShapes){
                        
                        if(letter[j]!= 'i' && letter[j] !='j' && letter[j] !='!' && letter[j] != '?'){

                            
                            if( ofInsidePoly(x, y, resamples[j+index].getVertices()) && !ofInsidePoly(x, y, resamples[j+index+1].getVertices()) ){
                                
                                if(posCount % PARTICLE_NUM == 0) {
                                    
                                    
                                    particle * p = new particle();
                                    p->setInitialCondition(x, y, 0, 0);
                                    particles.push_back(p);
                                    
                                }
                                
                                posCount++;
                                
                            }
                        } else {
                            
                            
                            if( ofInsidePoly(x, y, resamples[j+index].getVertices()) || ofInsidePoly(x, y, resamples[j+index+1].getVertices())  ){
                                
                                posCount++;
                                
                                if(posCount % PARTICLE_NUM == 0) {
                                    
                                    
                                    particle * p = new particle();
                                    p->setInitialCondition(x, y, 0, 0);
                                    particles.push_back(p);
                                    
                                    
                                    
                                }
                                
                            } //end if Poly
                            
                        }
                        
                        
                    } else {
                        
                        
                        if( ofInsidePoly(x, y, resamples[j+index].getVertices()) ){
                            
                            posCount++;
                            
                            if(posCount % PARTICLE_NUM == 0) {
                                
                                
                                particle * p = new particle();
                                p->setInitialCondition(x, y, 0, 0);
                                particles.push_back(p);
                                
                                
                            }
                            
                        } //end if Poly
                        
                        
                    } //end if/else bTwoShapes
                    
                } //end for loop y
            }//end for loop x
        }//end if letter = _
        
        if (bTwoShapes) index++;
    }

    
}

//-------------------------------------------------------------------------------------

void Phrase::update() {
    
    
    timer = ofGetElapsedTimeMillis() - start;
    
    switch (animation) {
            
        case EXPLODE:
            updateExplode();
            break;
            
        case BREAKER:
            updateBreak();
            break;
            
        case AGE:
            updateAge();
            break;
        case MOVE:
            updateFlock();
            break;
        case SWIRL:
            updateSwirl();
 
    }
    
    
    
    if(timer > 30000) {
        if(ofGetFrameNum() % 90 == 0){
            if(color.a > 0) color.a--;

        }
    }

    
}

void Phrase::updateBreak(){
    
    for (int i = 0; i < particles.size(); i++){
		particles[i]->resetForce();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		if(timer > 28000) particles[i]->addForce(ofNoise(particles[i]->pos.x),0);
		particles[i]->addRepulsionForce(ofGetWidth()/2, ofGetHeight()/2, 10, 1.5);
	}
    
	
	for (int i = 0; i < springs.size(); i++){
        if(timer > 10000){ 
            
            float increase = springs[i].distance* 0.001f;
            springs[i].distance += increase;
            //springs[i].distance += ofNoise(springs[i].particleA->pos.x);
            
        }
        springs[i].update();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->bounceOffWalls();
		particles[i]->addDampingForce();
		particles[i]->update();
	}
    
    
    
    
}

void Phrase::updateAge(){
    
    int numpoints = (int) ofMap(timer, 0, 35000, 6, 30);
    
    resamples.clear();
    
    for (int i = 0; i < lines.size(); i ++) {
		
		ofPolyline lineResampled = lines[i].getResampledBySpacing(numpoints);
        //lineResampled.setClosed(true);
        //ofPolyline lineSmoothed = lineResampled.getSmoothed(3);
		
		resamples.push_back(lineResampled);
        resamples[i].setClosed(true);
        resamples[i].getSmoothed(30);
        
	}
    

    
    
}

void Phrase::updateFlock() {
    if (timer > 16000 && timer < 20000){
        
        sort( particles.begin(), particles.end(), comparitor );
        
        for (int i =0; i<particles.size(); i++) 
            particles[i]->resetForce();
        
        
        for (int i = 0; i < particles.size(); i++) {
            //for(int j = 0; j < i; j++){
            for(int j = i-1; j >= 0; j--){
                
                if (fabs(particles[j]->pos.x - particles[i]->pos.x) > 10 ) break; 
                
                particles[i]->addRepulsionForce(*particles[j], 2, 1.1f);
                particles[i]->addAttractionForce(*particles[j], 1/*20*/, 0.005f);
                
            }
            
        }
        
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i]->addDampingForce();
            particles[i]->update();
        }
        
        
    } else if (timer > 20000 && timer < 30000){
        //sort( particles.begin(), particles.end(), comparitor );
        for (int i = 0; i < particles.size(); i++){
            particles[i]->cohesion.distance = 2.1f;
            particles[i]->alignment.distance = 50;
            particles[i]->seperation.distance = 2;
            
            
            particles[i]->cohesion.strength = 0.04f;
            particles[i]->alignment.strength = 0.08f;
            particles[i]->seperation.strength = 0.04f;
            
            particles[i]->damping = 0.12f;
            
        }
        
        
        // on every frame 
        // we reset the forces
        // add in any forces on the particle
        // perfom damping and
        // then update
        
        for (int i = 0; i < particles.size(); i++){
            particles[i]->resetForce();
        }
        
        
        for (int i = 0; i < particles.size(); i++){
            for (int j = 0; j < particles.size(); j++){
                if (i != j){
                    particles[i]->addForFlocking(*particles[j]);	
                }
            }
            
            // this was something we tried in class (partitcle move away from mouse...)
            particles[i]->addRepulsionForce(ofGetWidth()/2, ofGetHeight()/2, 40, 0.4);
        }
        
        for (int i = 0; i < particles.size(); i++){
            particles[i]->addFlockingForce();
            particles[i]->addDampingForce();
            particles[i]->update();
        }
        
        
        // wrap torroidally.
//        for (int i = 0; i < particles.size(); i++){
//            ofVec2f pos = particles[i]->pos;
//            if (pos.x < 0) pos.x = ofGetWidth();
//            if (pos.x > ofGetWidth()) pos.x = 0;
//            if (pos.y < 0) pos.y = ofGetHeight();
//            if (pos.y > ofGetHeight()) pos.y = 0;
//            particles[i]->pos = pos;
//        }
    
        
    } else if(timer > 30000) {
        
        for (int i = 0; i < particles.size(); i++){
            for (int j = 0; j < particles.size(); j++){
                if (i != j){
                    particles[i]->addForFlocking(*particles[j]);	
                }
            }
            
            //        for (int i = 0; i < particles.size(); i++) {
            //            //for(int j = 0; j < i; j++){
            //            for(int j = i-1; j >= 0; j--){
            //                
            //                if (fabs(particles[j]->pos.x - particles[i]->pos.x) > 10 ) break; 
            //                
            //                particles[i]->addRepulsionForce(*particles[j], 2, 1.1f);
            //                particles[i]->addAttractionForce(*particles[j], 10/*20*/, 0.005f);
            //                
            //            }
            //            
            //        }
            
            
            
            // this was something we tried in class (partitcle move away from mouse...)
            particles[i]->addAttractionForce(ofGetWidth()/2, ofGetHeight(), 45, 0.6);
        }
        
    }
    
    
}

void Phrase::updateSwirl() {
    
    if(timer > 16000 && timer < 20000){
        
    }else if (timer > 20000){
        
        for (int i =0; i <particles.size(); i++) {
            particles[i]->resetForce();
        }
        
        for (int i =0; i <particles.size(); i++) {
            particles[i]->resetForce();
        }
        
        for (int i = 0; i < particles.size(); i++) {
            
            particle part; 
            part.setInitialCondition(totalLength/2, pos.y, 0, 0);
            
            particles[i]->addClockwiseForce(part, 500, 1.2);
            //particles[i]->addCounterClockwiseForce(part, 40, 5);
        }
    
        for(int i = 0; i < particles.size(); i++){
            
            
            particles[i]->update();
        }
    }
    
    
    
}

void Phrase::updateExplode() {
    
    if(timer > 16000 && timer < 20000){
        
        sort( particles.begin(), particles.end(), comparitor );
        
        for (int i =0; i<particles.size(); i++) 
            particles[i]->resetForce();
        
        
        for (int i = 0; i < particles.size(); i++) {
            //for(int j = 0; j < i; j++){
            for(int j = i-1; j >= 0; j--){
                
                if (fabs(particles[j]->pos.x - particles[i]->pos.x) > 10 ) break; 
                
                particles[i]->addRepulsionForce(*particles[j], 2, 1.1f);
                particles[i]->addAttractionForce(*particles[j], 10/*20*/, 0.005f);
                
            }
            
        }
        
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i]->addDampingForce();
            particles[i]->update();
        }
        
    } else if(timer > 21000){
        
        //cout << "greater than 2000" << endl;
        
        //remove();
        
        sort( particles.begin(), particles.end(), comparitor );
        
//        for (int i = 0; i < particles.size(); i++) 
//            particles[i]->bounceOffWalls();
        
        for (int i =0; i<particles.size(); i++) 
            particles[i]->resetForce();
        
        
        for (int i = 0; i < particles.size(); i++) 
            particles[i]->addForce(0, ofNoise(particles[i]->pos.x, particles[i]->pos.y) );
        
        
        
        
        for (int i = 0; i < particles.size(); i++) {
            //for(int j = 0; j < i; j++){
            for(int j = i-1; j >= 0; j--){
                
                if (fabs(particles[j]->pos.x - particles[i]->pos.x) > 10 ) break; 
                particles[i]->addRepulsionForce(*particles[j], 25, 1.1f);
                particles[i]->addAttractionForce(*particles[j], 20, 0.005f);
                
            }
            
        }
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i]->addDampingForce();
            particles[i]->update();
        }
        
        
    }
    
}

void Phrase:: updatePos(Phrase * _p){
    
    
    if(pos.x > _p->pos.x && pos.x < _p->pos.x+_p->totalLength) {
        
        pos.x++;
        _p->pos.x--;
        
    }
//    
//    if(pos.y > _p->pos.y && pos.y < _p->pos.y+font->getLineHeight()) {
//        
//        pos.y++;
//        _p->pos.y--;
//        
//    }
    
}
//-------------------------------------------------------------------------------------

void Phrase::draw() {
    
    switch(animation){
        case BREAKER:
            drawParticlesAs(true);
            ofPushStyle();
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            for (int i = 0; i < springs.size(); i++){
                ofSetColor(color);
                springs[i].draw();
            }
            ofDisableSmoothing();
            ofDisableAlphaBlending();
            ofPopStyle();
            break;
            
        case EXPLODE:
            
            if (timer > 16000)
                drawParticlesAs(true);
            else drawCharactersAs(true);
        
            break;
        case AGE:
            drawCharactersAs(true);
            break;
        case MOVE:
            if (timer > 15900)
                drawParticlesAs(true);
            else drawCharactersAs(true);
        case SWIRL:
            if (timer > 1590)
                drawParticlesAs(true);
            else drawCharactersAs(true);
            
    }

    
}

//-------------------------------------------------------------------------------------





//-------------------------------------------------------------------------------------


void Phrase:: drawParticlesAs(bool fill) {
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    for (int i = 0; i < particles.size(); i++) {
        
        particles[i]->draw(fill, &color);
        
    }
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopStyle();
}

//-------------------------------------------------------------------------------------

void Phrase:: drawCharactersAs(bool fill) {
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetColor(color);
    
    if(fill) ofFill();
    else ofNoFill();
    
	index = 0;
    bTwoShapes = false;
	for (int j = 0; j < character.size(); j++) {
		
        
        if(character[j].getOutline().size() > 1) bTwoShapes = true;
            else bTwoShapes = false;
                
                float tempSpace;
        float kearning = 10;
        
        if (j > 0)
            tempSpace = letterBox[j-1].width +kearning;
            else 
                spacing = tempSpace = 0;
                
                spacing +=  tempSpace;
                
                
                
                if(letter[j] != '_'){
                    
                    resamples[j+index].draw();
                    
                    if (bTwoShapes) resamples[j+index+1].draw();
                        
                        
                        ofBeginShape();
                        
                        for (int i = 0; i < resamples[j+index].getVertices().size(); i++){
                            
                            ofVertex(resamples[j+index].getVertices()[i]);
                            
                            //ofCircle(resamples[j+index].getVertices()[i].x, resamples[j+index].getVertices()[i].y, 2);
                            
                        }
                    ofEndShape(true);
                    
                    
                    if (bTwoShapes){
                        ofPushStyle();
                        
                        if(letter[j]!= 'i' && letter[j] !='j' && letter[j] !='k' && letter[j] !='!' && letter[j] != '?' && letter[j]!= ':' && letter[j]!= ';')
                            //ofSetColor(bg);
                            
                            if(fill) ofSetColor(bg->r, bg->g, bg->b);
                            
                            //ofSet
                            
                            ofBeginShape();
                            
                            for (int i =0; i< resamples[j+index+1].getVertices().size(); i++) {
                                
                                ofVertex(resamples[j+index+1].getVertices()[i]);
                                
                                
                                //ofCircle(resamples[j+index+1].getVertices()[i].x, resamples[j+index+1].getVertices()[i].y, 2);
                            }
                        
                        ofEndShape(true);
                        ofPopStyle();
                    }
                }
        
        
        if(bTwoShapes) index++;
        
    }
    
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopStyle();
}
//------------------------------------------------------------------------------------

string Phrase::ofChartoString(char c){
    
    stringstream ss;
    string s;
    
    ss << c;
    ss >> s;
    
    return s;
    
}


