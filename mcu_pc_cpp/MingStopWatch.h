#ifndef  MingStopWatch_H
#define  MingStopWatch_H


class MingStopWatch
{
public:
    MingStopWatch();
	double now();
    void start();
    void stop();
    double getElapsedTime(); //in s
	double getDeltatTime();
	long long getDeltatTime_us();
		
private:
    LARGE_INTEGER m_start;
	LARGE_INTEGER m_now;
	LARGE_INTEGER m_old;
    LARGE_INTEGER m_stop;
    LARGE_INTEGER m_frequency;
};


MingStopWatch::MingStopWatch()
{
    m_start.QuadPart = 0;
    m_stop.QuadPart = 0;
	QueryPerformanceCounter(&m_now);
	QueryPerformanceCounter(&m_old);
    QueryPerformanceFrequency(&m_frequency);
}

double MingStopWatch::now()
{	
    QueryPerformanceCounter(&m_now);	
    return (double)m_now.QuadPart / (double)m_frequency.QuadPart;	
}

void MingStopWatch::start()
{
    QueryPerformanceCounter(&m_start);
}

void MingStopWatch::stop()
{
    QueryPerformanceCounter(&m_stop);
}

double MingStopWatch::getElapsedTime()
{
    LARGE_INTEGER time;
    time.QuadPart = m_stop.QuadPart - m_start.QuadPart;
    return (double)time.QuadPart / (double)m_frequency.QuadPart;
}

double MingStopWatch::getDeltatTime()
{	
	LARGE_INTEGER time;
	QueryPerformanceCounter(&m_now);
    time.QuadPart = m_now.QuadPart - m_old.QuadPart;
	QueryPerformanceCounter(&m_old);
    return (double)time.QuadPart / (double)m_frequency.QuadPart;	
}

long long MingStopWatch::getDeltatTime_us()
{	
	long long t_us=1000000*getDeltatTime();	
    return t_us;	
}


#endif