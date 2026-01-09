//
// Created by jnadeau on 11/16/2022.
//

#ifndef UTILS_SINGLETON_BASE_H
#define UTILS_SINGLETON_BASE_H

namespace utils {

    template <class T>
    class SingletonBase
    {
    public:
        SingletonBase(const SingletonBase&) = delete;
        SingletonBase(SingletonBase&&) = delete;
        SingletonBase& operator=(const SingletonBase&) = delete;
        SingletonBase& operator=(SingletonBase&&) = delete;
        virtual ~SingletonBase() = default;

        static T& getInstance()
        {
            static T singleton;
            return singleton;
        }
    protected:
        SingletonBase() = default;
    };
}   // namespace bfv::utils

#endif // UTILS_SINGLETON_BASE_H
