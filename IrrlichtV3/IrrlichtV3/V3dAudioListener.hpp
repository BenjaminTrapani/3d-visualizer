//
//  AudioListener.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/16/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef AudioListener_hpp
#define AudioListener_hpp

#include <stdio.h>
#include <portaudio.h>
#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include <memory>
#include "concurrentqueue.h"

namespace Viz3d{
    
    class V3dAudioListener{
    public:
        V3dAudioListener(const unsigned long framesPerBuffer, const unsigned long fftBins);
        ~V3dAudioListener();
        
        std::vector<std::string> getDevices()const;
        void start(PaDeviceIndex deviceIndex);
        void stop();
        
        inline void updateEQVals(const Aquila::SampleType * pData, const unsigned long framesPerBuffer){
            _fft->setN(_fftBins);
            _eqVals = _fft->fft(pData);
            int index = 0;
            for (auto iter = _eqVals.begin(); iter != _eqVals.end(); ++iter) {
                double magnitude = sqrt(iter->real()*iter->real() + iter->imag() * iter->imag());
               
                if(isnan(magnitude))
                    //_pFftResult[index] = 0;
                    return;
                else
                    _pFftResult[index] = magnitude;
                
                ++index;
            }
        }
        inline const std::atomic<double>* getFftResult()const{
            return _pFftResult;
        }
        inline double getSampleFrequency()const{
            return _sampleFrequency;
        }
        inline unsigned long getFramesPerBuffer()const{
            return _framesPerBuffer;
        }
        inline unsigned long getFftBinCount()const{
            return _fftBins;
        }
        
    private:
        const unsigned long _framesPerBuffer;
        const unsigned long _fftBins;
        std::atomic<double> * _pFftResult;
        Aquila::SpectrumType _eqVals;
        PaStream * _pInputStream;
        std::shared_ptr<Aquila::Fft> _fft;
        double _sampleFrequency;
        //moodycamel::ConcurrentQueue<Aquila::SpectrumType> _fftQueue;
    };
}

#endif /* AudioListener_hpp */
