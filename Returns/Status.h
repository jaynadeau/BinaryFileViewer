//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_STATUS_H
#define BINARYFILEVIEWER_STATUS_H


#include "ErrorBase.h"

#include <string>
#include <optional>

namespace qti::aisw::bfv::returns {

    template <typename ResultType = void>
    class Status
    {
    public:

        Status()
            : mError{std::nullopt}
            , mResult{std::nullopt}
            , mMessage{"Operation completed successfully."}
        {}

        explicit Status(const ResultType& r)
            : mError{std::nullopt}
            , mResult{r}
            , mMessage{"Operation completed successfully."}
        {}

        explicit Status(const ErrorBase& error)
            : mError{error}
            , mResult{std::nullopt}
            , mMessage{mError.value().getErrorAsString()}
        {}

        Status(const ResultType& result, const ErrorBase& error)
            : mError{error}
            , mResult{result}
            , mMessage{mError.value().getErrorAsString()}
        {}

        Status(Status&& other) noexcept
            : Status()
        {
            swap(*this, other);
        }

        Status(const Status& other)
            : mError{other.mError}
            , mResult{other.mResult}
            , mMessage{other.mMessage}
        {}

        explicit Status(const std::optional<ResultType>& other)
            : mError{std::nullopt}
            , mResult{other}
            , mMessage{"Operation completed successfully."}
        {}

        explicit Status(const std::optional<ErrorBase>& other)
            : mError{other}
            , mResult{std::nullopt}
            , mMessage{other.has_value()?other.value().getErrorAsString():""}
        {}

        Status(const std::optional<ResultType>& otherResult, const std::optional<ErrorBase>& otherError)
            : mError{otherError}
            , mResult{otherResult}
            , mMessage{otherError.has_value()?otherError.value().getErrorAsString():""}
        {}

        virtual ~Status() = default;

        Status& operator=(Status rhs)
        {
            swap(*this, rhs);
            return *this;
        }

        Status& operator=(const ResultType& r)
        {
            mError.reset();
            mResult.emplace(r);
            mMessage = "Operation completed successfully.";
            return *this;
        }

        friend void swap(Status& lhs, Status& rhs)
        {
          using std::swap;  // enable ADL
          swap(lhs.mResult, rhs.mResult);
          swap(lhs.mError, rhs.mError);
          swap(lhs.mMessage, rhs.mMessage);
        }

        void createError()
        {
            ErrorBase error;
            mError.emplace(error);
            mResult.emplace(std::nullopt);
            mMessage = mError.value().getErrorAsString();
        }

        void createError(const ErrorBase& error)
        {
            mError.emplace(error);
            mResult.emplace(std::nullopt);
            mMessage = mError.value().getErrorAsString();
        }

        void createError(const ResultType& r)
        {
            ErrorBase error;
            mError.emplace(error);
            mResult.emplace(r);
            mMessage = mError.value().getErrorAsString();
        }

        void createSuccess()
        {
            mError.reset();
            mResult.reset(std::nullopt);
            mMessage = "Operation completed successfully.";
        }

        void createSuccess(const ResultType& result)
        {
            mError.reset();
            mResult.emplace(result);
            mMessage = "Operation completed successfully.";
        }

        [[nodiscard]] std::string getMessage() const
        {
            return mMessage;
        }

        [[nodiscard]] bool hasResult() const
        {
            return mResult.has_value();
        }

        ResultType getResult() const
        {
            if(hasResult())
            {
                return mResult.value();
            }
            return ResultType{};
        }

        void setResult(const ResultType& r)
        {
            mResult.emplace(r);
        }

        [[nodiscard]] bool hasError() const
        {
            return mError.has_value();
        }

        [[maybe_unused]] static constexpr int SYSTEM_ERROR = -1;

    private:
        std::optional<ErrorBase> mError;
        std::optional<ResultType> mResult;
        std::string mMessage;
    };

} // namespace qti::aisw::bfv::utils::returns

#endif //BINARYFILEVIEWER_STATUS_H
