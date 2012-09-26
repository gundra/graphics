#include "ApplicationBase.h"

#include "Display.h"

#include <unistd.h> 
#include <sys/time.h>
#include <pthread.h> 

class ApplicationBaseImpl
{
    public:
        ApplicationBaseImpl(int w, int h)
            : mIsRunning(false), mDisplay(w, h), mThread()
        {
        }

        bool mIsRunning;
        Display mDisplay;
        pthread_t mThread;
};

ApplicationBase::ApplicationBase(int w, int h)
    : m_impl(new ApplicationBaseImpl(w, h))
{
}

ApplicationBase::~ApplicationBase()
{
    if (isRunning())
        stop();

    if (m_impl)
        delete m_impl;
}

static void* applicationLoopTh(void* arg)
{
    ApplicationBase* gb = static_cast<ApplicationBase*>(arg);
    if (!gb)
        return NULL;

    struct timeval startTime;
    gettimeofday(&startTime, NULL);

    int elapsedMicroseconds = 0;

    struct timeval currTime = startTime;

    while (gb->isRunning()) 
    {
        struct timeval elapsedTime;
        gettimeofday(&elapsedTime, NULL);

        elapsedMicroseconds = (elapsedTime.tv_sec * 1000000 + elapsedTime.tv_usec) - (currTime.tv_sec * 1000000 + currTime.tv_usec);

        gettimeofday(&currTime, NULL);

        gb->update(elapsedMicroseconds);
        gb->draw(gb->getDisplay());
        gb->getDisplay().update();

        usleep(1*10*1000);
    }

    return gb;
}

void ApplicationBase::run()
{
    init();

    if(!m_impl->mIsRunning)
        m_impl->mIsRunning = pthread_create(&m_impl->mThread, 0, applicationLoopTh, this) == 0;
}

void ApplicationBase::stop()
{
    fprintf(stderr, "stopping...\n");

    if (isRunning())
    {
        m_impl->mIsRunning = false;
        pthread_join(m_impl->mThread, 0);
    }
}

bool ApplicationBase::isRunning() const
{
    return m_impl->mIsRunning;
}

void ApplicationBase::init()
{
}

void ApplicationBase::update(int elapsedTime)
{
}

const Display& ApplicationBase::getDisplay()
{
    return m_impl->mDisplay;
}

