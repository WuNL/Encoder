//
// Created by wunl on 18-8-7.
//

#include <include/videoEncoderFactory.h>

#include "videoEncoderFactory.h"
#include "config.h"

std::unique_ptr<encoder> video_encoder_factory::create (initParams &p)
{
    std::unique_ptr<encoder> ret;
#ifdef USE_INTEL
    if (p.codec == std::string("h264"))
    {
        ret = std::unique_ptr<encoder>(new h264Encoder(p.encoder_name));
        return ret;
    }
    if (p.codec == std::string("h265"))
    {
        ret = std::unique_ptr<encoder>(new h265Encoder(p.encoder_name));
        return ret;
    } else
    {
        ret = std::unique_ptr<encoder>(new fakeEncoder(p.encoder_name));
        return ret;
    }
    return nullptr;
#else
    ret = std::unique_ptr<encoder>(new fakeEncoder(p));
    return ret;
#endif
}
