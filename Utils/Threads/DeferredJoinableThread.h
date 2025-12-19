//
// Created by jnadeau on 11/17/2025.
//

#ifndef BINARYFILEVIEWER_DEFERREDJOINABLETHREAD_H
#define BINARYFILEVIEWER_DEFERREDJOINABLETHREAD_H

#include "JoinableThread.h"

#include <functional>
#include <utility>
#include <stdexcept>
#include <tuple>

namespace bfv::utils::threads {

    /**
     * @brief A thread wrapper that defers thread execution until explicitly started.
     *
     * This class extends the concept of JoinableThread by allowing you to construct
     * the thread object without immediately starting execution. This is useful when
     * you need to set up multiple threads before starting them, or when thread
     * creation and execution need to be separated.
     *
     *
     * @note This class is NOT thread-safe. Do not call start() from multiple threads
     * simultaneously. The intended use is to construct the object, then call start()
     * once from a single thread.
     */
    class DeferredJoinableThread {
    public:
        DeferredJoinableThread() : mStarted{false} {}
        DeferredJoinableThread(DeferredJoinableThread&& other) noexcept
            : mTask{std::move(other.mTask)}
              , mStarted{other.mStarted}
              , mThread{std::move(other.mThread)}
        {
            other.mStarted = false;
        }
        DeferredJoinableThread& operator=(DeferredJoinableThread&& other) noexcept {
            if (this != &other) {
                mTask = std::move(other.mTask);
                mStarted = other.mStarted;
                mThread = std::move(other.mThread);
                other.mStarted = false;
            }
            return *this;
        }

        DeferredJoinableThread(const DeferredJoinableThread&) = delete;
        DeferredJoinableThread& operator=(const DeferredJoinableThread&) = delete;

        /**
         * @brief Constructs a deferred thread with the given callable and arguments.
         *
         * The thread is NOT started immediately. Call start() to begin execution.
         *
         * @tparam Callable The type of the callable object (function, lambda, member function, etc.)
         * @tparam Args The types of arguments to pass to the callable
         */
        template<typename Callable, typename... Args>
        explicit DeferredJoinableThread(Callable&& callable, Args&&... args)
            : mTask{[callable = std::forward<Callable>(callable),
                ...args = std::forward<Args>(args)]() mutable {
                callable(std::move(args)...);
            }}
            , mStarted(false)
        {}

        /**
         * @brief Destructor that automatically joins the thread if it's joinable.
         */
        ~DeferredJoinableThread() = default;

        /**
         * @brief Starts the thread execution.
         *
         * This method creates and starts the underlying JoinableThread with the
         * stored callable and arguments. Can only be called once.
         *
         * @throws std::logic_error if the thread has already been started
         *
         * @note After calling start(), the stored callable and arguments are moved
         * and should not be accessed. The object remains in a valid state for
         * destruction and move operations.
         */
        void start() {
            if (mStarted) {
                throw std::logic_error("Thread has already been started");
            }

            auto newThread = JoinableThread(std::move(mTask));
            mThread = std::move(newThread);
            mStarted = true;
        }

        /**
         * @brief Checks if the thread has been started.
         *
         * @return true if start() has been called, false otherwise
         */
        [[nodiscard]] bool isStarted() const noexcept {
            return mStarted;
        }

        /**
         * @brief Joins the thread if it's joinable.
         */
        void join() {
            mThread.join();
        }

        /**
         * @brief Checks if the thread is joinable.
         *
         * @return true if the thread is joinable, false otherwise
         */
        [[nodiscard]] bool joinable() const noexcept {
            return mThread.joinable();
        }

        /**
        * @brief Detaches the thread if it's joinable.
        */
        void detach() {
            mThread.detach();
        }

        /**
         * @brief Gets the thread ID.
         *
         * @return The thread ID
         */
        std::thread::id getId() const noexcept {
            return mThread.getId();
        }

        /**
         * @brief returns an implementation-defined, platform-specific
         * handle to the underlying OS thread
         *
         * Provides an escape hatch for interoperability with non‑standard
         * APIs—things you can’t do through the C++ standard library
         *
         * @return The native handle
         */
        std::thread::native_handle_type getNativeHandle() {
            return mThread.getNativeHandle();
        }

        /**
         * @brief Resets the thread with a new callable and arguments.
         *
         * Allows reusing the DeferredJoinableThread object after the previous
         * thread has completed. The thread must not be running (joinable).
         *
         * @tparam Callable The type of the callable object (function, lambda, member function, etc.)
         * @tparam Args The types of arguments to pass to the callable
         * @throws std::logic_error if the thread is currently running
         */
        template<typename Callable, typename... Args>
        void reset(Callable&& callable, Args&&... args) {
            if (mThread.joinable()) {
                throw std::logic_error("Cannot reset while thread is running");
            }
            mTask = [callable = std::forward<Callable>(callable),
                ...args = std::forward<Args>(args)]() mutable {
                        callable(std::move(args)...);
            };
            mStarted = false;
        }

        /**
         * @brief Swaps the contents of this thread with another.
         *
         * @param other The other DeferredJoinableThread to swap with
         */
        void swap(DeferredJoinableThread& other) noexcept {
            using std::swap;
            swap(mTask, other.mTask);
            swap(mStarted, other.mStarted);
            mThread.swap(other.mThread);
        }

    private:
        // /**
        //  * @brief Helper method to create the thread by unpacking stored arguments.
        //  *
        //  * Uses index_sequence to unpack the tuple of arguments.
        //  */
        // template<std::size_t... Is>
        // JoinableThread createThread(std::index_sequence<Is...>) {
        //     return JoinableThread(
        //         [callable = std::move(mCallable),
        //          args = std::move(mArgs)]() mutable {
        //             std::apply(std::move(callable), std::move(args));
        //         }
        //     );
        // }

        std::function<void()> mTask;
        bool mStarted;
        JoinableThread mThread;
    };

    /**
     * @brief Helper function to create a DeferredJoinableThread with a member function.
     *
     * This function simplifies the creation of a deferred thread that calls a member
     * function on an object instance.
     *
     * @tparam Class The class type
     * @tparam ReturnType The return type of the member function
     * @tparam Args The argument types of the member function
     * @param obj Pointer to the object instance
     * @param memberFunc Pointer to the member function
     * @param args Arguments to pass to the member function
     * @return A DeferredJoinableThread configured to call the member function
     *
     * Example usage:
     * @code
     * class MyClass {
     * public:
     *     void myMethod(int x, std::string s) { ... }
     * };
     *
     * MyClass obj;
     * auto thread = makeDeferredMemberThread(&obj, &MyClass::myMethod, 42, "hello");
     * thread.start();
     * @endcode
     */
    template<typename Class, typename ReturnType, typename... Args, typename... ActualArgs>
    auto makeDeferredMemberThread(
        Class* obj,
        ReturnType (Class::*memberFunc)(Args...),
        ActualArgs&&... args
    ) {
        return DeferredJoinableThread(
            [obj, memberFunc, ...capturedArgs = std::forward<ActualArgs>(args)]() mutable {
                (obj->*memberFunc)(std::move(capturedArgs)...);
            }
        );
    }

    /**
     * @brief Helper function for const member functions.
     */
    template<typename Class, typename ReturnType, typename... Args, typename... ActualArgs>
    auto makeDeferredMemberThread(
        const Class* obj,
        ReturnType (Class::*memberFunc)(Args...) const,
        ActualArgs&&... args
    ) {
        return DeferredJoinableThread(
            [obj, memberFunc, ...capturedArgs = std::forward<ActualArgs>(args)]() mutable {
                (obj->*memberFunc)(std::move(capturedArgs)...);
            }
        );
    }

}

#endif //BINARYFILEVIEWER_DEFERREDJOINABLETHREAD_H
