#include "thread.hpp"
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include <thread>

Mutex mt(false);
Mutex rmt(true);

void no_rlock(int id)
{
    int ret;
    while (true) {
        // pthread_mutex_lock встаёт в ожидание или занимает мутекс в любом случае.
        // pthread_mutex_trylock возвращает ошибку 16 если мутекс занят и не встаёт в очередь
        ret = mt.lock();
        printf("%d lock %d %s\n", id, ret, strerror(ret));

        // если добавишь в нерекурсивный мутекс еще lock будет deadlock

        printf("%d work\n", id);
        sleep(1); // симуляция работы

        ret = mt.unlock();
        printf("%d unlock %d %s\n\n", id, ret, strerror(ret));
        sleep(1); // пусть поспит иначе сразу же занимает поток
    }
}

void rlock(int id)
{
    int ret;
    while (true) {
        ret = rmt.lock();
        printf("%d lock %d %s\n", id, ret, strerror(ret));

        printf("%d work\n", id);
        sleep(1); // симуляция работы

        ret = rmt.lock(); // при рекурсивном локе инкрементируется внутренняя переменная
        printf("%d relock %d %s\n", id, ret, strerror(ret));

        printf("%d recursive work\n", id);
        sleep(1); // симуляция работы

        ret = rmt.unlock(); // при рекурсивном анлоке декрементируется внутренняя переменная
        printf("%d reunlock %d %s\n", id, ret, strerror(ret));

        // когда внутренняя переменная будет 0 рекурсивный мутекс освобождается
        ret = rmt.unlock();
        printf("%d unlock %d %s\n\n", id, ret, strerror(ret));
        sleep(1); // пусть поспит иначе сразу же занимает поток
    }
}

int main(int argc, char const *argv[])
{
#if REC
    auto func = rlock;
#else
    auto func = no_rlock;
#endif
    std::thread thr1(func, 1);
    std::thread thr2(func, 2);
    std::thread thr3(func, 3);

    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}