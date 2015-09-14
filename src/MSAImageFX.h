#pragma once

#include "ofMain.h"
#include "MSAPingPong.h"


namespace msa {
    class ImageFX {
    public:
        ImageFX();
        
        void allocate(int width, int height, int internalformat = GL_RGBA, int numSamples = 0);
        void allocate(ofFbo::Settings settings = ofFbo::Settings());
        
        // copy external source internally
        void copy(ofBaseDraws &source);
        
        void startShader(ofShader &shader);
        
        // apply shader to internal source
        void applyShader();
        
        // apply shader to external source
        void applyShader(ofBaseDraws &source);
        
        void endShader();
        
        
        float getWidth();
        float getHeight();
        
        bool isAllocated();

        ofFbo& targetFbo();
		ofFbo& sourceFbo();
        
        // advanced
		void swapFbo();
        ofFbo& fbo(int i);
        
    protected:
        PingPong<ofFbo> _fboPingPong;
        
        ofShader *_shader;
        
    
    };
}
