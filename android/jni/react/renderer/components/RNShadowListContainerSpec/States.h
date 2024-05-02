#pragma once

#ifdef ANDROID
#include <folly/dynamic.h>
#include <react/renderer/mapbuffer/MapBuffer.h>
#include <react/renderer/mapbuffer/MapBufferBuilder.h>
#endif

namespace facebook::react {

class ShadowListContainerState {
public:
  ShadowListContainerState() = default;

#ifdef ANDROID
  ShadowListContainerState(ShadowListContainerState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class ShadowListItemState {
public:
  ShadowListItemState() = default;

#ifdef ANDROID
  ShadowListItemState(ShadowListItemState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

}