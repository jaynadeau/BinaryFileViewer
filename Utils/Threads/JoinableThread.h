//
// Created by jnadeau on 11/12/2025.
//

#ifndef BINARYFILEVIEWER_JOINABLETHREAD_H
#define BINARYFILEVIEWER_JOINABLETHREAD_H

#include <functional>
#include <thread>
#include <utility>

namespace bfv::utils::threads {

    /**
     * @brief RAII wrapper for std::thread that automatically joins on destruction.
     * Prevents common resource leaks from unjoined threads.
     */
    class JoinableThread {
    public:
        JoinableThread() = default;
        JoinableThread(JoinableThread&&) noexcept = default;
        JoinableThread& operator=(JoinableThread&&) noexcept = default;
        JoinableThread(const JoinableThread&) = delete;
        JoinableThread& operator=(const JoinableThread&) = delete;

        explicit JoinableThread(std::function<void()> func)
            : mThread{std::move(func)}
        {}

        ~JoinableThread() noexcept {
            if (mThread.joinable()) {
                mThread.join();
            }
        }

        void detach() {
            if (mThread.joinable()) {
                mThread.detach();
            }
        }

        void join() {
            if (mThread.joinable()) {
                mThread.join();
            }
        }

        bool joinable() const {
            return mThread.joinable();
        }

        // Add thread ID access
        std::thread::id getId() const {
            return mThread.get_id();
        }

        void swap(JoinableThread& other) noexcept {
            mThread.swap(other.mThread);
        }

        std::thread::native_handle_type getNativeHandle() {
            return mThread.native_handle();
        }

    private:
        std::thread mThread;
    };

    inline unsigned int hardware_concurrency() {
        return std::thread::hardware_concurrency();
    }

}

#endif //BINARYFILEVIEWER_JOINABLETHREAD_H
