//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_ENCODER_H
#define ENCODER_ENCODER_H

#include <iostream>
#include <string>
#include <functional>
#include <boost/utility.hpp>

#include <pthread.h>

#include "shmfifo.h"

#define BUFFERLEN 1920*1080*3/2

typedef struct videoBuffer
{
    int size;
    char buffer[BUFFERLEN];
} coded_video_buffer;

typedef struct yuvBuffer
{
    int size;
    char buffer[BUFFERLEN];
} raw_video_buffer;

enum
{
    h264,
    h264_hw,
    h265,
    h265_hw
};

typedef struct InitParams
{
    std::string encoder_name;
    std::string codec;
    int v_width;
    int v_height;
    int v_gop;
    int packetMode;
} initParams;

typedef struct InitParamsRet
{
    std::string encoder_name;
    bool success;
    int yuv_shmID;
    int out_shmID;
} initParamsRet;

class encoder : public boost::noncopyable
{
public:
    typedef std::function<void()> ErrHandleCallback;
    typedef std::function<void()> NotifyCloseCallback;

    explicit encoder (initParams p);

    virtual ~encoder();

    void setErrHandleCallback_(const ErrHandleCallback &errHandleCallback_)
    {
        encoder::errHandleCallback_ = errHandleCallback_;
    }

    void setNotifyCloseCallback_(const NotifyCloseCallback &notifyCloseCallback_)
    {
        encoder::notifyCloseCallback_ = notifyCloseCallback_;
    }

    const std::string &getName ()
    {
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
    virtual int encodeBuffer (void *in, void *out) = 0;

private:
    ErrHandleCallback errHandleCallback_;
    NotifyCloseCallback notifyCloseCallback_;

private:
    std::string encoder_name;

    static int raw_shm_id;
    static int codeced_shm_id;

protected:
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;

    shmfifo_t *raw_video_fifo_;
    shmfifo_t *coded_video_fifo_;

    raw_video_buffer raw_video_buffer_;
    coded_video_buffer coded_video_buffer_;
};


#endif //ENCODER_ENCODER_H
