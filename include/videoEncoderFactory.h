//
// Created by wunl on 18-8-7.
//

#ifndef ENCODER_VIDEOENCODERFACTORY_H
#define ENCODER_VIDEOENCODERFACTORY_H

#include <bits/unique_ptr.h>
#include "h264Encoder.h"
#include "h265Encoder.h"
#include "fakeEncoder.h"

class video_encoder_factory
{
public:
    static std::unique_ptr<encoder> create (initParams &p);
};


#endif //ENCODER_VIDEOENCODERFACTORY_H
