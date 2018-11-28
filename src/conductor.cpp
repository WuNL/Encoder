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
    int index = findEncoderByName(p.encoder_name);
    if (index != - 1)
    {
        encoderVec_[index]->waitForInitFinish();
//        std::cout << "initEncoder waitForInitFinish done" << std::endl;
//        encoderVec_[index]->stop();
        encoderVec_.erase(encoderVec_.begin() + index);

        std::unique_ptr<encoder> e = video_encoder_factory::create(p);
        encoderVec_.push_back(std::move(e));
        ret.encoder_name = p.encoder_name;
        ret.yuv_shmID = encoderVec_.back()->getRawId();
        ret.out_shmID = encoderVec_.back()->getCodecedId();
        ret.success = true;
        encoderVec_.back()->run();
    } else
    {
        std::unique_ptr<encoder> e = video_encoder_factory::create(p);
        encoderVec_.push_back(std::move(e));
        ret.encoder_name = p.encoder_name;
        ret.yuv_shmID = encoderVec_.back()->getRawId();
        ret.out_shmID = encoderVec_.back()->getCodecedId();
        ret.success = true;
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
//        std::cout << "encoderVec name:" << encoderVec_[i]->getName() << std::endl;
        if (encoderVec_[i]->getName() == name)
            return i;
    }
    return - 1;
}

conductor::conductor () : errHandleCallback_(nullptr),
                          notifyCloseCallback_(nullptr),
                          InitDoneCallback_(nullptr) {}

const bool conductor::destroyEncoder (destroyParams &p)
{
    int index = findEncoderByName(p.encoder_name);
    if (- 1 != index)
    {
        encoderVec_[index]->waitForInitFinish();
//        std::cout << "destroyEncoder waitForInitFinish done" << std::endl;
        encoderVec_.erase(encoderVec_.begin() + index);
    } else
    {
        std::cout << "destroyEncoder not find encoder" << std::endl;
    }
    std::cout << "destroyEncoder finish" << std::endl;
    return true;
}

const bool conductor::updateBitrate (initParams &p)
{
    int index = findEncoderByName(p.encoder_name);
    if (- 1 != index)
    {
        encoderVec_[index]->waitForInitFinish();
        std::cout << "updateBitrate waitForInitFinish done" << std::endl;
        encoderVec_[index]->updateBitrate(p.bitrate, p.framerate);
    } else
    {
        std::cout << "updateBitrate not find encoder" << std::endl;
    }
    std::cout << "updateBitrate finish" << std::endl;
    return true;
}

void conductor::forceKeyFrame(forceKeyFrameParams &p) {
    int index = findEncoderByName(p.encoder_name);
    if (-1 != index) {
        encoderVec_[index]->waitForInitFinish();
        std::cout << "forceKeyFrame waitForInitFinish done" << std::endl;
        encoderVec_[index]->forceKeyFrame(true);
    } else {
        std::cout << "forceKeyFrame not find encoder" << std::endl;
    }
    std::cout << "forceKeyFrame finish" << std::endl;
}
