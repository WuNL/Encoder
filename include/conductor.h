//
// Created by sdt on 18-8-6.
//

#ifndef ENCODER_CONDUCTOR_H
#define ENCODER_CONDUCTOR_H

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
private:

    ErrHandleCallback errHandleCallback_;
    NotifyCloseCallback notifyCloseCallback_;
};


#endif //ENCODER_CONDUCTOR_H
