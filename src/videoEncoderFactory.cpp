//
// Created by wunl on 18-8-7.
//

#include <include/videoEncoderFactory.h>

#include "videoEncoderFactory.h"

std::unique_ptr<encoder> video_encoder_factory::create(std::string codec)
{
    std::unique_ptr<encoder> ret;
    if (codec == std::string("h264"))
    {
        ret = std::unique_ptr<encoder>(new h264Encoder);
        return ret;
    }
    if (codec == std::string("h265"))
    {
        ret = std::unique_ptr<encoder>(new h265Encoder);
        return ret;
    } else
    {
        ret = std::unique_ptr<encoder>(new fakeEncoder);
        return ret;
    }
    return nullptr;
}
