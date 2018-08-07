//
// Created by sdt on 18-8-6.
//

#ifndef ENCODER_CONDUCTOR_H
#define ENCODER_CONDUCTOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <boost/utility.hpp>

#include "encoder.h"



class conductor:public boost::noncopyable
{
public:
    typedef std::function<void()> ErrHandleCallback;
    typedef std::function<void()> NotifyCloseCallback;
    void setErrHandleCallback(const ErrHandleCallback& cb)
    {
        errHandleCallback_ = cb;
    }

    const initParamsRet initEncoder(initParams& p);

private:
    int findEncoderByName(std::string& name);

private:

    ErrHandleCallback errHandleCallback_;
    NotifyCloseCallback notifyCloseCallback_;

    std::vector<std::unique_ptr<encoder> > encoderVec;
};


#endif //ENCODER_CONDUCTOR_H
