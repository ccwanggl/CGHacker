#include <chrono>
#include <iostream>
#include <string>

#include "CGHacker/Core/Log.h"

namespace CG
{
    class Timer
        {
        public:
            Timer(const char* name)
                : m_Name(name), m_Stopped(false)
            {
                m_StartTimepoint = std::chrono::steady_clock::now();
            }

            ~Timer()
            {
                if (!m_Stopped)
                    Stop();
            }

            void Stop()
            {
                auto endTimepoint = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

                CG_CORE_ERROR("{}  ----  {} ms", m_Name, elapsedTime.count() * 0.001f);
                m_Stopped = true;
            }
        private:
            const char* m_Name;
            std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
            bool m_Stopped;
        };
}
