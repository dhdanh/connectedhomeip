/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#pragma once

#include <lib/address_resolve/AddressResolve.h>
#include <lib/dnssd/Resolver.h>
#include <system/TimeSource.h>
#include <transport/raw/PeerAddress.h>

namespace chip {
namespace AddressResolve {
namespace Impl {

enum class NodeLookupResult
{
    kKeepSearching, // keep the current search active
    kLookupError,   // final status: error
    kLookupSuccess, // final status: success
};

/// Action to take when some resolve data
/// has been received by an active lookup
class NodeLookupAction
{
public:
    NodeLookupAction(const NodeLookupAction & other) { *this = other; }

    NodeLookupAction & operator=(const NodeLookupAction & other)
    {
        mResultType = other.mResultType;
        switch (mResultType)
        {
        case NodeLookupResult::kLookupError:
            mResult.error = other.mResult.error;
            break;
        case NodeLookupResult::kLookupSuccess:
            mResult.result = other.mResult.result;
            break;
        case NodeLookupResult::kKeepSearching:
            // no data is important here
            break;
        }
        return *this;
    }

    static NodeLookupAction KeepSearching() { return NodeLookupAction(NodeLookupResult::kKeepSearching); }

    static NodeLookupAction Error(CHIP_ERROR err)
    {
        NodeLookupAction value(NodeLookupResult::kLookupError);
        value.mResult.error = err;
        return value;
    }

    static NodeLookupAction Success(const AddressResolve::ResolveResult & result)
    {
        NodeLookupAction value(NodeLookupResult::kLookupSuccess);
        value.mResult.result = result;
        return value;
    }

    NodeLookupResult Type() const { return mResultType; }
    CHIP_ERROR ErrorResult() const { return mResult.error; }
    const AddressResolve::ResolveResult & ResolveResult() const { return mResult.result; }

private:
    NodeLookupAction(NodeLookupResult result) : mResultType(result) {}

    union
    {
        CHIP_ERROR error;
        AddressResolve::ResolveResult result;
    } mResult = {};
    NodeLookupResult mResultType;
};

/// An implementation of a node lookup handle
///
/// Keeps track of time requests as well as the current
/// "best" IP address found.
class NodeLookupHandle : public NodeLookupHandleBase
{
public:
    const NodeLookupRequest & GetRequest() const { return mRequest; }

    /// Sets up a request for a new lookup.
    /// Resets internal state (i.e. best address so far)
    void ResetForLookup(System::Clock::Timestamp now, const NodeLookupRequest & request);

    /// Mark that a specific IP address has been found
    void LookupResult(const ResolveResult & result);

    /// Called after timeouts or after a series of IP addresses have been
    /// marked as found.
    ///
    /// If sufficient data for a complete address resolution has been gathered,
    /// calls the underlying listener `OnNodeAddressResolved` and returns
    /// kStopSearching.
    ///
    /// Returns kKeepSearching if more data is acceptable (keep timeouts and
    /// any active searches)
    NodeLookupAction NextAction(System::Clock::Timestamp now);

    /// Return when the next timer (min or max lookup time) is required to
    /// be triggered for this lookup handle
    System::Clock::Timeout NextEventTimeout(System::Clock::Timestamp now);

private:
    System::Clock::Timestamp mRequestStartTime;
    NodeLookupRequest mRequest; // active request to process
    AddressResolve::ResolveResult mBestResult;
    unsigned mBestAddressScore = 0;
};

class Resolver : public ::chip::AddressResolve::Resolver, public Dnssd::OperationalResolveDelegate
{
public:
    virtual ~Resolver() = default;

    // AddressResolve::Resolver

    CHIP_ERROR Init(System::Layer * systemLayer) override;
    CHIP_ERROR LookupNode(const NodeLookupRequest & request, Impl::NodeLookupHandle & handle) override;

    // Dnssd::OperationalResolveDelegate

    void OnOperationalNodeResolved(const Dnssd::ResolvedNodeData & nodeData) override;
    void OnOperationalNodeResolutionFailed(const PeerId & peerId, CHIP_ERROR error) override;

private:
    static void OnResolveTimer(System::Layer * layer, void * context) { static_cast<Resolver *>(context)->HandleTimer(); }

    /// Timer on lookup node events: min and max search times.
    void HandleTimer();

    /// Sets up a system timer to the next closest timeout on one of the active
    /// lookup operations.
    ///
    /// Any existing timer is cancelled and then OnResolveTimer will be called
    /// on the closest event required for an active resolve.
    void ReArmTimer();

    /// Handles the 'NextAction' on the given iterator
    ///
    /// NOTE: may remove `current` from the internal list. Current MUST NOT
    /// be used after calling this method.
    void HandleAction(IntrusiveList<NodeLookupHandle>::Iterator & current);

    System::Layer * mSystemLayer = nullptr;
    Time::TimeSource<Time::Source::kSystem> mTimeSource;
    IntrusiveList<NodeLookupHandle> mActiveLookups;
};

} // namespace Impl
} // namespace AddressResolve
} // namespace chip
