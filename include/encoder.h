//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_ENCODER_H
#define ENCODER_ENCODER_H

#include <string>
#include <functional>
#include <boost/utility.hpp>

typedef struct InitParams{
    std::string encoder_name;
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

    /// \brief
    /// \param cb
    void setErrHandleCallback(const ErrHandleCallback& cb)
    {
        errHandleCallback_ = cb;
    }
    const std::string& getName(){
        return encoder_name;
    }

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
};


#endif //ENCODER_ENCODER_H
