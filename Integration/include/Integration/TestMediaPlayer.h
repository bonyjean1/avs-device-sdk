/*
 * TestMediaPlayer.h
 *
 * Copyright 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ALEXA_CLIENT_SDK_INTEGRATION_INCLUDE_INTEGRATION_TEST_PLAYER_INTERFACE_H_
#define ALEXA_CLIENT_SDK_INTEGRATION_INCLUDE_INTEGRATION_TEST_PLAYER_INTERFACE_H_

#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#include <future>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>
#include <AVSCommon/Utils/MediaPlayer/MediaPlayerObserverInterface.h>
#include "AVSCommon/Utils/Timing/Timer.h"

namespace alexaClientSDK {
namespace integration {
namespace test {

/**
 * A Mock MediaPlayer that attempts to alert the observer of playing and stopping without
 * actually playing audio. This removes the dependancy on an audio player to run tests with 
 * SpeechSynthesizer
 */
class TestMediaPlayer : public avsCommon::utils::mediaPlayer::MediaPlayerInterface {
public:
    // Destructor.
    ~TestMediaPlayer();

    avsCommon::utils::mediaPlayer::MediaPlayerStatus setSource(
            std::shared_ptr<avsCommon::avs::attachment::AttachmentReader> attachmentReader) override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus setSource(
            std::shared_ptr<std::istream> stream, bool repeat) override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus setSource(const std::string& url) override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus play() override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus stop() override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus pause() override;

    avsCommon::utils::mediaPlayer::MediaPlayerStatus resume() override;

    int64_t getOffsetInMilliseconds() override;

    void setObserver(
            std::shared_ptr<avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface> playerObserver) override;

private:
    /// Observer to notify of state changes.
    std::shared_ptr<avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface> m_observer;
    /// Flag to indicate when a playback finished notification has been sent to the observer.
    bool m_playbackFinished = false;
    /// The AttachmentReader to read audioData from.
    std::shared_ptr<avsCommon::avs::attachment::AttachmentReader> m_attachmentReader;
    /// Timer to wait to send onPlaybackFinished to the observer.
    std::shared_ptr<avsCommon::utils::timing::Timer> m_timer;
    // istream for Alerts. 
    std::shared_ptr<std::istream> m_istream; 
};
} // namespace test
} // namespace integration
} // namespace alexaClientSDK

#endif // ALEXA_CLIENT_SDK_INTEGRATION_INCLUDE_INTEGRATION_TEST_PLAYER_INTERFACE_H_
