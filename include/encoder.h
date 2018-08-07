//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_ENCODER_H
#define ENCODER_ENCODER_H

#include <string>
#include <functional>
#include <boost/utility.hpp>

#include <pthread.h>

enum
{
    h264,
    h264_hw,
    h265,
    h265_hw
};

typedef struct InitParams{
    std::string encoder_name;
    std::string codec;
    int v_width;
    int v_height;
    int v_gop;
    int packetMode;
}initParams;

typedef struct InitParamsRet{
    std::string encoder_name;
    bool success;
    int yuv_shmID;
    int out_shmID;
}initParamsRet;

class encoder:public boost::noncopyable
{
public:
    typedef std::function<void()> ErrHandleCallback;
    typedef std::function<void()> NotifyCloseCallback;

    virtual ~encoder();

    void setErrHandleCallback_(const ErrHandleCallback &errHandleCallback_)
    {
        encoder::errHandleCallback_ = errHandleCallback_;
    }

    void setNotifyCloseCallback_(const NotifyCloseCallback &notifyCloseCallback_)
    {
        encoder::notifyCloseCallback_ = notifyCloseCallback_;
    }
    const std::string& getName(){
        return encoder_name;
    }

    bool started() const { return started_; }

    pid_t tid() const { return tid_; }

    virtual void run() = 0;

    virtual int join() = 0; // return pthread_join()

private:
    /// \brief
    /// \param in
    /// \param out
    /// \return
    virtual int encodeBuffer(void* in, void* out) = 0;

private:
    ErrHandleCallback errHandleCallback_;
    NotifyCloseCallback notifyCloseCallback_;

private:
    std::string encoder_name;

    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
};


#endif //ENCODER_ENCODER_H
