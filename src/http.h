//
//  http.h
//  letters
//
//  Created by Chris Piuggi on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
//  Connect to a database to check for incoming texts

#pragma once

//#include "ofxThread.h"
//#include "ofxHttpUtils.h"
//#include "ofxHttpTypes.h"

class HTTPConnect {
public:
    
    void setup();
    void checkDB();
    
    void response(ofxHttpResponse &response);
    void sendURL(string _id);
    
    bool databaseInfo();
    
    string baseURL;
    string responseStr;
    int responseError;
    
    ofxHttpForm form;
    ofxHttpUtils httpUtils;
    
    
};