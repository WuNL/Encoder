//
// Created by wunl on 18-8-7.
//

#ifndef ENCODER_FAKEENCODER_H
#define ENCODER_FAKEENCODER_H

#include "encoder.h"

class fakeEncoder : public encoder
{
public:
    void run();

    virtual int join() override;

private:
    int encodeBuffer(void *in, void *out) {}
};


#endif //ENCODER_FAKEENCODER_H
