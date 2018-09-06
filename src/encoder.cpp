#include <utility>

//
// Created by wunl on 18-8-5.
//

#include <include/encoder.h>

#include "encoder.h"
#include <assert.h>

int encoder::raw_shm_id = 1000;
int encoder::codeced_shm_id = 2000;

encoder::~encoder ()
{
    started_ = false;

    if (raw_video_fifo_)
        shmfifo_destroy(raw_video_fifo_);
    if (coded_video_fifo_)
        shmfifo_destroy(coded_video_fifo_);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_cond_destroy(&finish_threshold_cv);
//    pthread_exit(NULL);

}

encoder::encoder (initParams p) : errHandleCallback_(nullptr), notifyCloseCallback_(nullptr),
                                  encoder_name(std::move(p.encoder_name)),
                                  params(p),
                                  started_(false),
                                  initFinished(false),
                                  readyToEndThread(false),
                                  raw_video_fifo_(nullptr),
                                  coded_video_fifo_(nullptr)
{
    /*初始化互斥量和条件变量对象*/
    pthread_mutex_init(&count_mutex, nullptr);
    pthread_cond_init(&count_threshold_cv, nullptr);
    pthread_cond_init(&finish_threshold_cv, nullptr);

    // 创建共享内存相关内容
    raw_video_fifo_ = shmfifo_init(raw_shm_id, sizeof(raw_video_buffer), 30);
//    std::cout << raw_video_fifo_->sem_mutex << std::endl;
    raw_shm_id_local = raw_shm_id;
    raw_shm_id += 10;
    assert(raw_shm_id < 2000);
    coded_video_fifo_ = shmfifo_init(codeced_shm_id, sizeof(coded_video_buffer), 30);
    codeced_shm_id_local = codeced_shm_id;
    codeced_shm_id += 10;
    assert(raw_shm_id < 3000);
}
