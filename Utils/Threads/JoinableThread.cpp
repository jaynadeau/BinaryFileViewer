//
// Created by jnadeau on 11/12/2025.
//

#include "JoinableThread.h"

namespace utils::threads {

    JoinableThread::JoinableThread(std::function<void()> func)
    : mThread{std::move(func)}
    {}

    JoinableThread::~JoinableThread() noexcept {
        if (mThread.joinable()) {
            mThread.join();
        }
    }

    void JoinableThread::detach() {
        if (mThread.joinable()) {
            mThread.detach();
        }
    }

    void JoinableThread::join() {
        if (mThread.joinable()) {
            mThread.join();
        }
    }

    bool JoinableThread::joinable() const {
        return mThread.joinable();
    }

    // Add thread ID access
    std::thread::id JoinableThread::getId() const {
        return mThread.get_id();
    }

    void JoinableThread::swap(JoinableThread& other) noexcept {
        mThread.swap(other.mThread);
    }

    std::thread::native_handle_type JoinableThread::getNativeHandle() {
        return mThread.native_handle();
    }

}
