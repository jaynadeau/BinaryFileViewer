//
// Created by jnadeau on 11/16/2022.
//

#ifndef BINARYFILEVIEWER_SINGLETONBASE_H
#define BINARYFILEVIEWER_SINGLETONBASE_H

namespace qti::aisw::bfv::utils {

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
}   // namespace qti::aisw::bfv::utils

#endif //BINARYFILEVIEWER_SINGLETONBASE_H
