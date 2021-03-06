//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_ENCODER_H
#define ENCODER_ENCODER_H

#include <functional>
#include <boost/utility.hpp>

class encoder:public boost::noncopyable
{
public:
    typedef std::function<void()> ErrHandleCallback;
    typedef std::function<void()> NotifyCloseCallback;

    /// \brief
    /// \param cb
    void setErrHandleCallback(const ErrHandleCallback& cb)
    {
        errHandleCallback_ = cb;
    }

private:
    /// \brief
    /// \param in
    /// \param out
    /// \return
    virtual int encodeBuffer(void* in, void* out) = 0;

    ErrHandleCallback errHandleCallback_;
    NotifyCloseCallback notifyCloseCallback_;
};


#endif //ENCODER_ENCODER_H
