#pragma once

#include <ReactCommon/JavaTurboModule.h>
#include <ReactCommon/TurboModule.h>
#include <jsi/jsi.h>
#include <react/renderer/components/RNShadowListContainerSpec/ComponentDescriptors.h>
#include <react/renderer/components/RNShadowListItemSpec/ComponentDescriptors.h>

namespace facebook::react {

JSI_EXPORT
std::shared_ptr<TurboModule> RNShadowListContainerSpec_ModuleProvider(const std::string &moduleName, const JavaTurboModule::InitParams &params);

}
