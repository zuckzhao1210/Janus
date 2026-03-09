/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef CYBER_TRANSPORT_TRANSPORT_H_
#define CYBER_TRANSPORT_TRANSPORT_H_

#include <atomic>
#include <memory>
#include <string>

#include "cyber/proto/transport_conf.pb.h"

#include "cyber/common/macros.h"
#include "cyber/transport/qos/qos_profile_conf.h"
#include "cyber/transport/receiver/receiver.h"
#include "cyber/transport/rtps/participant.h"
#include "cyber/transport/transmitter/rtps_transmitter.h"
#include "cyber/transport/receiver/rtps_receiver.h"
#include "cyber/transport/transmitter/transmitter.h"

namespace apollo {
namespace cyber {
namespace transport {

using apollo::cyber::proto::OptionalMode;

class Transport {
 public:
  virtual ~Transport();

  void Shutdown();

  template <typename M>
  auto CreateTransmitter(const RoleAttributes& attr,
                         const OptionalMode& mode = OptionalMode::HYBRID) ->
      typename std::shared_ptr<Transmitter<M>>;

  template <typename M>
  auto CreateReceiver(const RoleAttributes& attr,
                      const typename Receiver<M>::MessageListener& msg_listener,
                      const OptionalMode& mode = OptionalMode::HYBRID) ->
      typename std::shared_ptr<Receiver<M>>;

  ParticipantPtr participant() const { return participant_; }

 private:
  void CreateParticipant();

  std::atomic<bool> is_shutdown_ = {false};
  ParticipantPtr participant_ = nullptr;

  DECLARE_SINGLETON(Transport)
};

template <typename M>
auto Transport::CreateTransmitter(const RoleAttributes& attr,
                                  const OptionalMode& mode) ->
    typename std::shared_ptr<Transmitter<M>> {
  if (is_shutdown_.load()) {
    AINFO << "transport has been shut down.";
    return nullptr;
  }

  std::shared_ptr<Transmitter<M>> transmitter = nullptr;
  RoleAttributes modified_attr = attr;
  if (!modified_attr.has_qos_profile()) {
    modified_attr.mutable_qos_profile()->CopyFrom(
        QosProfileConf::QOS_PROFILE_DEFAULT);
  }

  transmitter = std::make_shared<RtpsTransmitter<M>>(modified_attr, participant());

  RETURN_VAL_IF_NULL(transmitter, nullptr);
  transmitter->Enable();

  return transmitter;
}

template <typename M>
auto Transport::CreateReceiver(
    const RoleAttributes& attr,
    const typename Receiver<M>::MessageListener& msg_listener,
    const OptionalMode& mode) -> typename std::shared_ptr<Receiver<M>> {
  if (is_shutdown_.load()) {
    AINFO << "transport has been shut down.";
    return nullptr;
  }

  std::shared_ptr<Receiver<M>> receiver = nullptr;
  RoleAttributes modified_attr = attr;
  if (!modified_attr.has_qos_profile()) {
    modified_attr.mutable_qos_profile()->CopyFrom(
        QosProfileConf::QOS_PROFILE_DEFAULT);
  }

  receiver = std::make_shared<RtpsReceiver<M>>(modified_attr, msg_listener);

  RETURN_VAL_IF_NULL(receiver, nullptr);
  if (mode != OptionalMode::HYBRID) {
    receiver->Enable();
  }
  return receiver;
}

}  // namespace transport
}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_TRANSPORT_TRANSPORT_H_
