//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_H264ENCODER_H
#define ENCODER_H264ENCODER_H

#include "encoder.h"

class h264Encoder : public encoder
{
public:
    virtual void run() override;

    explicit h264Encoder (initParams p);

    virtual int join() override;

private:
    int encodeBuffer (void *in, void *out) override {}

    static void *start (void *threadarg);

    void encodeBuffer ();
};


#endif //ENCODER_H264ENCODER_H
