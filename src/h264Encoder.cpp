#include <utility>

//
// Created by wunl on 18-8-5.
//

#include <include/h264Encoder.h>

#include "h264Encoder.h"
#include <utime.h>

void h264Encoder::run()
{
    started_ = true;
    pthread_create(&pthreadId_, nullptr, &h264Encoder::start, static_cast<void *>(this));
}

int h264Encoder::join()
{
    return 0;
}

h264Encoder::h264Encoder (initParams p) : encoder(std::move(p))
{

}

void *h264Encoder::start (void *threadarg)
{
    auto this_ptr = static_cast<h264Encoder *>(threadarg);

    this_ptr->encodeBuffer();
}

void h264Encoder::encodeBuffer ()
{
    while (started_)
    {
        usleep(1000000);
        std::cout << "sleeping!" << std::endl;
    }
}
