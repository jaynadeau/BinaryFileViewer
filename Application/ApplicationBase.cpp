//
// Created by jnadeau on 1/24/2026.
//

#include "ApplicationBase.h"

namespace application {

ApplicationBase::ApplicationBase() {

}

void ApplicationBase::start() {
    APPLICATION_STATE currentState = mStateFlag.load();
    if (currentState == APPLICATION_STATE::UNKNOWN) {
        mStateFlag.store(application::APPLICATION_STATE::STARTED);
    }
}

void ApplicationBase::stop() {
    APPLICATION_STATE currentState = mStateFlag.load();
    if (currentState == APPLICATION_STATE::RUNNING || currentState == APPLICATION_STATE::PAUSED) {
        mStateFlag.store(application::APPLICATION_STATE::STOPPED);
    }
}

void ApplicationBase::restart() {
    APPLICATION_STATE currentState = mStateFlag.load();
    if (currentState == APPLICATION_STATE::STARTED || currentState == APPLICATION_STATE::PAUSED) {
        stop();
        start();
    }
}

void ApplicationBase::pause() {
    APPLICATION_STATE currentState = mStateFlag.load();
    if (currentState == APPLICATION_STATE::STARTED) {
        mStateFlag.store(application::APPLICATION_STATE::PAUSED);
    }
}

void ApplicationBase::resume() {
    APPLICATION_STATE currentState = mStateFlag.load();
    if (currentState == APPLICATION_STATE::PAUSED) {
        mStateFlag.store(application::APPLICATION_STATE::STARTED);
    }
}




} // application
