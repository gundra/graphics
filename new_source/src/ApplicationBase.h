#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H

class Display;
class ApplicationBaseImpl;

class ApplicationBase
{
    public:
        ApplicationBase(int w, int h);
        virtual ~ApplicationBase();

        void run();
        void stop();
        bool isRunning() const;

        virtual void init();
        virtual void update(int elapsedTime);
        virtual void draw(const Display& dis) = 0;

        const Display& getDisplay();

    private:
        ApplicationBaseImpl* m_impl;

        ApplicationBase(const ApplicationBase&);
        ApplicationBase& operator=(const ApplicationBase&);
};

#endif /* APPLICATIONBASE_H */
