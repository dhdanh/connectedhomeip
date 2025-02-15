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

// THIS FILE IS GENERATED BY ZAP

#pragma once

#include <app-common/zap-generated/af-structs.h>
#include <app-common/zap-generated/cluster-objects.h>
#include <app/InteractionModelEngine.h>
#include <app/data-model/DecodableList.h>
#include <app/util/af-enums.h>
#include <app/util/attribute-filter.h>
#include <app/util/im-client-callbacks.h>
#include <inttypes.h>
#include <lib/support/FunctionTraits.h>
#include <lib/support/Span.h>

// List specific responses
void ApplicationBasicClusterAllowedVendorListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                 chip::Callback::Cancelable * onSuccessCallback,
                                                                 chip::Callback::Cancelable * onFailureCallback);
typedef void (*ApplicationBasicAllowedVendorListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::VendorId> & data);
void ApplicationBasicClusterServerGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                          chip::Callback::Cancelable * onSuccessCallback,
                                                                          chip::Callback::Cancelable * onFailureCallback);
typedef void (*ApplicationBasicServerGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void ApplicationBasicClusterClientGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                          chip::Callback::Cancelable * onSuccessCallback,
                                                                          chip::Callback::Cancelable * onFailureCallback);
typedef void (*ApplicationBasicClientGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void ApplicationBasicClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data,
                                                             chip::Callback::Cancelable * onSuccessCallback,
                                                             chip::Callback::Cancelable * onFailureCallback);
typedef void (*ApplicationBasicAttributeListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void ContentLauncherClusterAcceptHeaderListAttributeFilter(chip::TLV::TLVReader * data,
                                                           chip::Callback::Cancelable * onSuccessCallback,
                                                           chip::Callback::Cancelable * onFailureCallback);
typedef void (*ContentLauncherAcceptHeaderListAttributeCallback)(void * context,
                                                                 const chip::app::DataModel::DecodableList<chip::CharSpan> & data);
void ContentLauncherClusterServerGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                         chip::Callback::Cancelable * onSuccessCallback,
                                                                         chip::Callback::Cancelable * onFailureCallback);
typedef void (*ContentLauncherServerGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void ContentLauncherClusterClientGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                         chip::Callback::Cancelable * onSuccessCallback,
                                                                         chip::Callback::Cancelable * onFailureCallback);
typedef void (*ContentLauncherClientGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void ContentLauncherClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data,
                                                            chip::Callback::Cancelable * onSuccessCallback,
                                                            chip::Callback::Cancelable * onFailureCallback);
typedef void (*ContentLauncherAttributeListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void GeneralCommissioningClusterServerGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                              chip::Callback::Cancelable * onSuccessCallback,
                                                                              chip::Callback::Cancelable * onFailureCallback);
typedef void (*GeneralCommissioningServerGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void GeneralCommissioningClusterClientGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                              chip::Callback::Cancelable * onSuccessCallback,
                                                                              chip::Callback::Cancelable * onFailureCallback);
typedef void (*GeneralCommissioningClientGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void GeneralCommissioningClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                 chip::Callback::Cancelable * onSuccessCallback,
                                                                 chip::Callback::Cancelable * onFailureCallback);
typedef void (*GeneralCommissioningAttributeListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void KeypadInputClusterServerGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                     chip::Callback::Cancelable * onSuccessCallback,
                                                                     chip::Callback::Cancelable * onFailureCallback);
typedef void (*KeypadInputServerGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void KeypadInputClusterClientGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                     chip::Callback::Cancelable * onSuccessCallback,
                                                                     chip::Callback::Cancelable * onFailureCallback);
typedef void (*KeypadInputClientGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void KeypadInputClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data, chip::Callback::Cancelable * onSuccessCallback,
                                                        chip::Callback::Cancelable * onFailureCallback);
typedef void (*KeypadInputAttributeListListAttributeCallback)(void * context,
                                                              const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void OperationalCredentialsClusterFabricsListAttributeFilter(chip::TLV::TLVReader * data,
                                                             chip::Callback::Cancelable * onSuccessCallback,
                                                             chip::Callback::Cancelable * onFailureCallback);
typedef void (*OperationalCredentialsFabricsListAttributeCallback)(
    void * context,
    const chip::app::DataModel::DecodableList<
        chip::app::Clusters::OperationalCredentials::Structs::FabricDescriptor::DecodableType> & data);
void OperationalCredentialsClusterTrustedRootCertificatesListAttributeFilter(chip::TLV::TLVReader * data,
                                                                             chip::Callback::Cancelable * onSuccessCallback,
                                                                             chip::Callback::Cancelable * onFailureCallback);
typedef void (*OperationalCredentialsTrustedRootCertificatesListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::ByteSpan> & data);
void TargetNavigatorClusterTargetListListAttributeFilter(chip::TLV::TLVReader * data,
                                                         chip::Callback::Cancelable * onSuccessCallback,
                                                         chip::Callback::Cancelable * onFailureCallback);
typedef void (*TargetNavigatorTargetListListAttributeCallback)(
    void * context,
    const chip::app::DataModel::DecodableList<chip::app::Clusters::TargetNavigator::Structs::TargetInfo::DecodableType> & data);
void TargetNavigatorClusterServerGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                         chip::Callback::Cancelable * onSuccessCallback,
                                                                         chip::Callback::Cancelable * onFailureCallback);
typedef void (*TargetNavigatorServerGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void TargetNavigatorClusterClientGeneratedCommandListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                         chip::Callback::Cancelable * onSuccessCallback,
                                                                         chip::Callback::Cancelable * onFailureCallback);
typedef void (*TargetNavigatorClientGeneratedCommandListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::CommandId> & data);
void TargetNavigatorClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data,
                                                            chip::Callback::Cancelable * onSuccessCallback,
                                                            chip::Callback::Cancelable * onFailureCallback);
typedef void (*TargetNavigatorAttributeListListAttributeCallback)(
    void * context, const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
