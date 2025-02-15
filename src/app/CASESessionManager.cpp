/*
 *
 *    Copyright (c) 2020-2021 Project CHIP Authors
 *    All rights reserved.
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

#include <app/CASESessionManager.h>
#include <lib/address_resolve/AddressResolve.h>

namespace chip {

CHIP_ERROR CASESessionManager::Init(chip::System::Layer * systemLayer)
{
    return AddressResolve::Resolver::Instance().Init(systemLayer);
}

CHIP_ERROR CASESessionManager::FindOrEstablishSession(PeerId peerId, Callback::Callback<OnDeviceConnected> * onConnection,
                                                      Callback::Callback<OnDeviceConnectionFailure> * onFailure)
{
    Dnssd::ResolvedNodeData resolutionData;

    bool nodeIDWasResolved =
#if CHIP_CONFIG_MDNS_CACHE_SIZE > 0
        (mConfig.dnsCache != nullptr && mConfig.dnsCache->Lookup(peerId, resolutionData) == CHIP_NO_ERROR);
#else
        false;
#endif

    OperationalDeviceProxy * session = FindExistingSession(peerId);
    if (session == nullptr)
    {
        // TODO - Implement LRU to evict least recently used session to handle mActiveSessions pool exhaustion
        if (nodeIDWasResolved)
        {
            session = mConfig.devicePool->Allocate(mConfig.sessionInitParams, peerId, resolutionData);
        }
        else
        {
            session = mConfig.devicePool->Allocate(mConfig.sessionInitParams, peerId);
        }

        if (session == nullptr)
        {
            onFailure->mCall(onFailure->mContext, peerId, CHIP_ERROR_NO_MEMORY);
            return CHIP_ERROR_NO_MEMORY;
        }
    }
    else if (nodeIDWasResolved)
    {
        session->OnNodeIdResolved(resolutionData);
    }

    CHIP_ERROR err = session->Connect(onConnection, onFailure);
    if (err != CHIP_NO_ERROR)
    {
        // Release the peer rather than the pointer in case the failure handler has already released the session.
        ReleaseSession(peerId);
    }

    return err;
}

void CASESessionManager::ReleaseSession(PeerId peerId)
{
    ReleaseSession(FindExistingSession(peerId));
}

void CASESessionManager::ReleaseSessionsForFabric(CompressedFabricId compressedFabricId)
{
    mConfig.devicePool->ReleaseDevicesForFabric(compressedFabricId);
}

void CASESessionManager::ReleaseAllSessions()
{
    mConfig.devicePool->ReleaseAllDevices();
}

CHIP_ERROR CASESessionManager::GetPeerAddress(PeerId peerId, Transport::PeerAddress & addr)
{
#if CHIP_CONFIG_MDNS_CACHE_SIZE > 0
    if (mConfig.dnsCache != nullptr)
    {
        Dnssd::ResolvedNodeData resolutionData;
        // TODO(andy31415): DNS caching is generally not populated, need to move
        // caching into a the address resolve layer and not have a global one anymore.
        if (mConfig.dnsCache->Lookup(peerId, resolutionData) == CHIP_NO_ERROR)
        {
            addr = OperationalDeviceProxy::ToPeerAddress(resolutionData);
            return CHIP_NO_ERROR;
        }
    }
#endif

    OperationalDeviceProxy * session = FindExistingSession(peerId);
    VerifyOrReturnError(session != nullptr, CHIP_ERROR_NOT_CONNECTED);
    addr = session->GetPeerAddress();
    return CHIP_NO_ERROR;
}

OperationalDeviceProxy * CASESessionManager::FindSession(const SessionHandle & session)
{
    return mConfig.devicePool->FindDevice(session);
}

OperationalDeviceProxy * CASESessionManager::FindExistingSession(PeerId peerId)
{
    return mConfig.devicePool->FindDevice(peerId);
}

void CASESessionManager::ReleaseSession(OperationalDeviceProxy * session)
{
    if (session != nullptr)
    {
        mConfig.devicePool->Release(session);
    }
}

} // namespace chip
