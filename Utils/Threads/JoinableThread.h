//
// Created by jnadeau on 11/12/2025.
//

#ifndef THREADS_JOINABLETHREAD_H
#define THREADS_JOINABLETHREAD_H

#include <functional>
#include <thread>
#include <utility>

namespace utils::threads {

    /**
     * @brief RAII wrapper for std::thread that automatically joins on destruction.
     *
     * JoinableThread provides a safer alternative to std::thread by ensuring that
     * threads are properly joined before destruction, preventing resource leaks and
     * potential std::terminate() calls from unjoined threads.
     *
     * Key features:
     * - Automatic joining in destructor if thread is joinable
     * - Move-only semantics (non-copyable)
     * - Thin wrapper around std::thread with minimal overhead
     *
     * @note This class is move-only and cannot be copied.
     * @note If the thread is detached before destruction, no join occurs.
     *
     * Example usage:
     * @code
     * JoinableThread worker([]() {
     *     // Thread work here
     * });
     * // Thread automatically joins when worker goes out of scope
     * @endcode
     */
    class JoinableThread {
    public:
        /**
         * @brief Default constructor. Creates a thread object that represents no thread.
         */
        JoinableThread() = default;
        /**
         * @brief Constructs a JoinableThread and starts execution of the provided function.
         * @param func The function to execute in the new thread
         * @throws std::system_error if the thread could not be started
         *
         * Example:
         * @code
         * JoinableThread t([]() { std::cout << "Hello from thread\n"; });
         * @endcode
         */
        explicit JoinableThread(std::function<void()> func);
        /**
         * @brief Move constructor. Transfers ownership of the thread.
         * @param other The JoinableThread to move from
         */
        JoinableThread(JoinableThread&&) noexcept = default;
        /**
         * @brief Move assignment operator. Transfers ownership of the thread.
         * @param other The JoinableThread to move from
         * @return Reference to this object
         * @note If this object already manages a joinable thread, it will be joined first
         */
        JoinableThread& operator=(JoinableThread&&) noexcept = default;
        /**
         * @brief Copy constructor (deleted). JoinableThread cannot be copied.
         */
        JoinableThread(const JoinableThread&) = delete;
        /**
         * @brief Copy assignment operator (deleted). JoinableThread cannot be copied.
         */
        JoinableThread& operator=(const JoinableThread&) = delete;
        /**
         * @brief Destructor. Automatically joins the thread if it is joinable.
         * @note This is noexcept - if join() throws, std::terminate() will be called
         */
        ~JoinableThread() noexcept;

        /**
         * @brief Detaches the thread, allowing it to execute independently.
         *
         * After calling detach(), the thread continues execution independently and
         * will not be joined in the destructor.
         *
         * @throws std::system_error if the thread is not joinable
         * @note Once detached, you cannot rejoin the thread
         */
        void detach();
        /**
         * @brief Blocks until the thread completes execution.
         * @throws std::system_error if the thread is not joinable or if a deadlock is detected
         * @note After join() completes, joinable() will return false
         */
        void join();
        /**
         * @brief Checks if the thread is joinable.
         * @return true if the thread is joinable (active and not detached), false otherwise
         * @note A default-constructed thread is not joinable
         * @note A thread that has been joined or detached is not joinable
         */
        bool joinable() const;
        /**
         * @brief Gets the thread ID.
         * @return The ID of the managed thread, or a default-constructed thread::id if no thread
         * @note Returns a default ID if the thread is not joinable
         */
        std::thread::id getId() const;
        /**
         * @brief Swaps the state of this thread with another.
         * @param other The JoinableThread to swap with
         */
        void swap(JoinableThread& other) noexcept;
        /**
         * @brief Gets the native handle for the underlying thread.
         * @return The platform-specific native thread handle
         * @note The type and meaning of the native handle is platform-dependent
         * @warning Use with caution - direct manipulation of native handles can lead to undefined behavior
         */
        std::thread::native_handle_type getNativeHandle();
    private:
        /** @brief The underlying std::thread object */
        std::thread mThread;
    };

    /**
     * @brief Returns the number of concurrent threads supported by the implementation.
     * @return The number of hardware thread contexts, or 0 if the value is not computable or well-defined
     *
     * This is a convenience wrapper around std::thread::hardware_concurrency() and can be
     * used to determine an appropriate number of threads for parallel operations.
     *
     * Example:
     * @code
     * unsigned int num_threads = hardware_concurrency();
     * if (num_threads == 0) num_threads = 2; // fallback value
     * @endcode
     */
    inline unsigned int hardware_concurrency() {
        return std::thread::hardware_concurrency();
    }

}

#endif //THREADS_JOINABLETHREAD_H
