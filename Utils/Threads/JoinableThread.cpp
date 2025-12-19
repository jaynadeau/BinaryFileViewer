//
// Created by jnadeau on 11/12/2025.
//

#include "JoinableThread.h"

namespace bfv::utils::threads {

    // template<typename Callable, typename... Args>
    // JoinableThread::JoinableThread(Callable&& callable, Args&&... args)
    // {
    //     mWorker = std::bind(std::forward<Callable>(callable), std::forward<Args>(args)...);
    //     mThread = std::thread(mWorker);
    // }
    //
    // JoinableThread::~JoinableThread() {
    //     if (mThread.joinable()) {
    //         mThread.join();
    //     }
    // }

}
