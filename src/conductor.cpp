//
// Created by sdt on 18-8-6.
//

#include <include/conductor.h>
#include <cstring>
#include "videoEncoderFactory.h"

const initParamsRet conductor::initEncoder (initParams &p)
{
    initParamsRet ret;
    memset(&ret, 0x00, sizeof(initParamsRet));

    if (findEncoderByName(p.encoder_name) != - 1)
    {

        ret.success = false;
        return ret;
    } else
    {
        std::unique_ptr<encoder> e = video_encoder_factory::create(p);
        encoderVec_.push_back(std::move(e));
        encoderVec_.back()->run();
    }

    if (InitDoneCallback_)
    {
        InitDoneCallback_();
    }
    return ret;
}

int conductor::findEncoderByName (std::string &name)
{
    for (int i = 0; i < encoderVec_.size(); ++ i)
    {
        std::cout << name << "-----------" << encoderVec_[i]->getName() << std::endl;
        if (encoderVec_[i]->getName() == name)
            return i;
    }
    return - 1;
}

conductor::conductor () : errHandleCallback_(nullptr),
                          notifyCloseCallback_(nullptr),
                          InitDoneCallback_(nullptr) {}
