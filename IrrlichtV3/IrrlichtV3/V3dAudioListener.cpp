//
//  AudioListener.cpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/16/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#include "V3dAudioListener.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>
#include "aquila/source/window/HannWindow.h"

using namespace Viz3d;

V3dAudioListener::V3dAudioListener(const unsigned long framesPerBuffer, const unsigned long fftBins):
_framesPerBuffer(framesPerBuffer), _fftBins(fftBins){
    
    PaError error = Pa_Initialize();
    if(error != paNoError){
        throw std::invalid_argument("Failed to initialize port audio.");
    };

    _fft = Aquila::FftFactory::getFft(framesPerBuffer);
    _pFftResult = new std::atomic<double> [framesPerBuffer];
    memset(_pFftResult, 0.0, framesPerBuffer);
}

V3dAudioListener::~V3dAudioListener(){
    stop();
    
    PaError error = Pa_Terminate();
    if(error != paNoError){
        throw std::invalid_argument("Failed to terminate port audio.");
    };
    
    delete [] _pFftResult;
    _pFftResult = nullptr;
}

double Hann (double N, double n )
{
     return 0.5 * ( 1.0 - cos( 2.0 * M_PI * n / (N - 1.0) ));
}

double Hamm (double N, double n){
    return 0.54 - 0.46*cos(2*M_PI * n / (N-1.0));
}
static int coreAudioCallback( const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData ){
    memcpy(outputBuffer, inputBuffer, framesPerBuffer * sizeof(double));
    
    double windowedData[framesPerBuffer];
    const double * doubleInBuf = (const double*)inputBuffer;
    
    V3dAudioListener * pCallingListener = (V3dAudioListener*)userData;
    //Apply hann window function to input
    for(int i = 0; i < framesPerBuffer; ++i){
        windowedData[i]= doubleInBuf[i] * Hamm((double)framesPerBuffer, (double)i);
    }
    
    if (statusFlags & paInputOverflow) {
        printf("Input underflow\n");
        return 0;
    }
    
    if(statusFlags & paInputOverflow){
        printf("Input overflow\n");
        return 0;
    }
    if (statusFlags & paOutputUnderflowed) {
        printf("Output underflowed\n");
        return 0;
    }
    if (statusFlags & paOutputOverflow) {
        printf("Output overflow\n");
        return 0;
    }
    
    Aquila::SampleType * out = (Aquila::SampleType*)windowedData;
    pCallingListener->updateEQVals(out, framesPerBuffer);
    
    return 0;
}

std::vector<std::string> V3dAudioListener::getDevices()const{
    int numDevices = Pa_GetDeviceCount();
    std::vector<std::string> result;
    result.reserve(numDevices);
    const PaDeviceInfo *deviceInfo;
    for( int i=0; i<numDevices; i++ )
    {
        deviceInfo = Pa_GetDeviceInfo( i );
        result.push_back(std::string(deviceInfo->name));
    }
    return result;
}

void V3dAudioListener::start(PaDeviceIndex deviceIndex){
    PaError error = 0;
    
    PaStreamParameters inputParams;
    inputParams.device = Pa_GetDefaultOutputDevice();
    inputParams.channelCount = 2;
    inputParams.sampleFormat = paFloat32;
    const PaDeviceInfo * inputInfo = Pa_GetDeviceInfo(inputParams.device);
    inputParams.suggestedLatency = inputInfo->defaultLowOutputLatency;
    inputParams.hostApiSpecificStreamInfo = NULL;
    
    _sampleFrequency = inputInfo->defaultSampleRate;
    
    PaStreamParameters outputParams;
    outputParams.device = deviceIndex;
    outputParams.channelCount = 2;
    outputParams.sampleFormat = paFloat32;
    const PaDeviceInfo * outputInfo = Pa_GetDeviceInfo(outputParams.device);
    outputParams.suggestedLatency = outputInfo->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;

    /* Open an audio output stream. */
    
    error = Pa_OpenStream(&_pInputStream,
                          &inputParams,
                          &outputParams,
                                 outputInfo->defaultSampleRate,
                                 _framesPerBuffer,
                                 0,
                                 coreAudioCallback,
                                 this);
    if( error != paNoError ){
        printf("Port audio error = %s", Pa_GetErrorText(error));
    }
    
    error = Pa_StartStream(_pInputStream);
    if( error != paNoError ){
        printf("Port audio error = %s", Pa_GetErrorText(error));
        throw std::invalid_argument("Failed to start port audio stream.");
    }

}

void V3dAudioListener::stop(){
    PaError error = Pa_AbortStream(_pInputStream);
    if(error != paNoError){
        printf("Failed to abort audio stream port audio.");
    }
}

