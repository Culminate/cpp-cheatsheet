#pragma once
#include <pthread.h>

class Mutex
{
public:
    Mutex(bool recursive = false)
    {
        pthread_mutexattr_init(&_mutex_attr);
        if (recursive) {
            pthread_mutexattr_settype(&_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
        } else {
            pthread_mutexattr_settype(&_mutex_attr, PTHREAD_MUTEX_NORMAL);
        }

        pthread_mutex_init(&_mutex, &_mutex_attr);
    };

    ~Mutex()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_mutexattr_destroy(&_mutex_attr);
    }

    int trylock()
    {
        return pthread_mutex_trylock(&_mutex);
    }

    int lock()
    {
        return pthread_mutex_lock(&_mutex);
    }

    int unlock()
    {
        return pthread_mutex_unlock(&_mutex);
    }
private:
    // условные переменные ...

    pthread_mutex_t _mutex;
    pthread_mutexattr_t _mutex_attr;
};