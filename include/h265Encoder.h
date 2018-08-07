//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_H265ENCODER_H
#define ENCODER_H265ENCODER_H

#include "encoder.h"

class h265Encoder : public encoder
{
public:
    virtual void run() override;

    virtual int join() override;

private:
    int encodeBuffer(void *in, void *out) {}
};


#endif //ENCODER_H265ENCODER_H
