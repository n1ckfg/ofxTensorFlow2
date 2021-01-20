#pragma once

#include "cppflow/cppflow.h"
#include "ofxTensor.h"

class ofxModel {

    public: 

    ofxModel() = default;
    
    ofxModel(std::string modelPath) {
        // todo check if boost::is_directory()
        if (false){
            ofLog() << "ofxModel: path not a folder!";
        }
        else {
            model_ = new cppflow::model(modelPath);
            if (!model_){
                ofLog() << "ofxModel: model not initialized!";
            }
            else {
                ofLog() << "ofxModel: loaded model: " << modelPath;
            }
        }
    }
    
    ofxTensor run(const cppflow::tensor & tensor){
        if (model_){
            return (*model_)(tensor);
        }
        else{
            ofLog() << "ofxModel: no model loaded! Returning tensor containing -1.";
            return ofxTensor(-1);
        }
    }

    int load(std::string modelPath) {
        if (model_){
            ofLog() << "ofxModel: delete current model";
            delete model_;
        }
        model_ = new cppflow::model(modelPath);

        if (!model_){
            ofLog() << "ofxModel: model not initialized!";
            return 0;
        }
        else {
            ofLog() << "ofxModel: loaded model: " << modelPath;
            return 1;
        }
    }

    private:

    cppflow::model * model_;

};