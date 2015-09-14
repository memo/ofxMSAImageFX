//
//  MSAImageFilter.cpp
//  MSAOpenCL_Demo
//
//  Created by Memo Akten on 29/06/2014.
//
//

#include "MSAImageFX.h"

namespace msa {
    ImageFX::ImageFX() {
        _shader = NULL;
    }
    
    void ImageFX::allocate(int width, int height, int internalformat, int numSamples) {
        for(int i=0; i<2; i++) _fboPingPong.at(i).allocate(width, height, internalformat, numSamples);
    }

    void ImageFX::allocate(ofFbo::Settings settings) {
        for(int i=0; i<2; i++) _fboPingPong.at(i).allocate(settings);
    }
    

    // copy external source internally
    void ImageFX::copy(ofBaseDraws &source) {
        targetFbo().begin();
        source.draw(0, 0, getWidth(), getHeight());
        targetFbo().end();
        swapFbo();
    }
    
    void ImageFX::startShader(ofShader &shader) {
        if(_shader) ofLogWarning() << "MSAImageFX::startShader - already have shader bound";
        _shader = &shader;
        _shader->begin();
    }
    
    // apply shader to internal source
    void ImageFX::applyShader() {
        applyShader(sourceFbo());

    }
    
    // apply shader to external source
    void ImageFX::applyShader(ofBaseDraws &source) {
        if(!_shader) {
            ofLogWarning() << "MSAImageFX::startShader - no shader bound";
            return;
        }
        
        targetFbo().begin();
        _shader->setUniformTexture("tex", sourceFbo(), 0);
        source.draw(0, 0, getWidth(), getHeight());
        targetFbo().end();
        swapFbo();
    }
    
    void ImageFX::endShader() {
        if(!_shader) {
            ofLogWarning() << "MSAImageFX::startShader - no shader bound";
            return;
        }
        _shader->end();
        _shader = NULL;
    }

    
    float ImageFX::getWidth() {
        return _fboPingPong.getTarget().getWidth();
    }
    
    float ImageFX::getHeight() {
        return _fboPingPong.getTarget().getHeight();
    }
    
    bool ImageFX::isAllocated() {
        return _fboPingPong.getTarget().isAllocated();
    }
    
    
    ofFbo& ImageFX::targetFbo() {
        return _fboPingPong.getTarget();
    }
    
    ofFbo& ImageFX::sourceFbo() {
        return _fboPingPong.getSource();
    }
    
    void ImageFX::swapFbo() {
        _fboPingPong.swap();
    }
    
    ofFbo& ImageFX::fbo(int i) {
        return _fboPingPong.at(i);
    }

}