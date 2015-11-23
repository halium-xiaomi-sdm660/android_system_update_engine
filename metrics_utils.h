//
// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UPDATE_ENGINE_METRICS_UTILS_H_
#define UPDATE_ENGINE_METRICS_UTILS_H_

#include "update_engine/connection_manager.h"
#include "update_engine/metrics.h"

namespace chromeos_update_engine {

class SystemState;

namespace metrics_utils {

// Transforms a ErrorCode value into a metrics::DownloadErrorCode.
// This obviously only works for errors related to downloading so if |code|
// is e.g. |ErrorCode::kFilesystemCopierError| then
// |kDownloadErrorCodeInputMalformed| is returned.
metrics::DownloadErrorCode GetDownloadErrorCode(ErrorCode code);

// Transforms a ErrorCode value into a metrics::AttemptResult.
//
// If metrics::AttemptResult::kPayloadDownloadError is returned, you
// can use utils::GetDownloadError() to get more detail.
metrics::AttemptResult GetAttemptResult(ErrorCode code);

// Calculates the internet connection type given |type| and |tethering|.
metrics::ConnectionType GetConnectionType(NetworkConnectionType type,
                                          NetworkTethering tethering);

// This function returns the duration on the wallclock since the last
// time it was called for the same |state_variable_key| value.
//
// If the function returns |true|, the duration (always non-negative)
// is returned in |out_duration|. If the function returns |false|
// something went wrong or there was no previous measurement.
bool WallclockDurationHelper(SystemState* system_state,
                             const std::string& state_variable_key,
                             base::TimeDelta* out_duration);

// This function returns the duration on the monotonic clock since the
// last time it was called for the same |storage| pointer.
//
// You should pass a pointer to a 64-bit integer in |storage| which
// should be initialized to 0.
//
// If the function returns |true|, the duration (always non-negative)
// is returned in |out_duration|. If the function returns |false|
// something went wrong or there was no previous measurement.
bool MonotonicDurationHelper(SystemState* system_state,
                             int64_t* storage,
                             base::TimeDelta* out_duration);

}  // namespace metrics_utils
}  // namespace chromeos_update_engine

#endif  // UPDATE_ENGINE_METRICS_UTILS_H_