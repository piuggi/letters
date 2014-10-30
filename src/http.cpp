//
//  http.cpp
//  letters
//
//  Created by Chris Piuggi on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "http.h"

void HTTPConnect::setup(){
    
    ofAddListener(httpUtils.newResponseEvent, this, &HTTPConnect::response);
    baseURL = "http://occupyyomama.org/joiner/visual/check.php";
    httpUtils.start();
    responseStr = "NULL";
    
}


void HTTPConnect::checkDB(){
    
    ofxHttpForm form;
    string makeURL = baseURL + "/?phrase";
    form.action = makeURL;
    form.method = OFX_HTTP_GET;
    httpUtils.addForm(form);
    cout << "Database checking..." << endl;
}


void HTTPConnect::response(ofxHttpResponse &response){
    
    responseError = response.status;
    
//    if(response.status == 200){
        responseStr = (string)response.responseBody;
//    }
    
    cout << "db response:" << responseStr << endl;

    
}

void HTTPConnect::sendURL(string _id ){
    
    cout << "Confirming Receipt...";
    
    ofxHttpForm form;
    form.action = baseURL;
    form.method = OFX_HTTP_POST;
    form.addFormField("id", _id);
    httpUtils.addForm(form);
    
    cout << "\t...Reciept Confirmed" << endl;
    
}

bool HTTPConnect::databaseInfo(){
    
    //cout << responseStr << endl;
    
    if( !responseStr.empty() && responseStr != "NULL" && responseStr != "DELIVERY_SUCCESS") {
        
        if(responseStr == "no") {
            return false;
            
        }else{ 
            return true;
        }
        
    } else {
        
        return false;
    }
}

