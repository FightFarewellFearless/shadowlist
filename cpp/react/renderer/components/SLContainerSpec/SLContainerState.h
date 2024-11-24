#pragma once

#include <react/renderer/graphics/Point.h>
#include <react/renderer/graphics/Size.h>
#include "SLFenwickTree.hpp"

#ifdef ANDROID
#include <folly/dynamic.h>
#include <react/renderer/mapbuffer/MapBuffer.h>
#include <react/renderer/mapbuffer/MapBufferBuilder.h>
#endif

namespace facebook::react {

#ifdef ANDROID
constexpr static MapBuffer::Key SLCONTAINER_STATE_CHILDREN_MEASUREMENTS_TREE = 0;
constexpr static MapBuffer::Key SLCONTAINER_STATE_VISIBLE_START_INDEX = 1;
constexpr static MapBuffer::Key SLCONTAINER_STATE_VISIBLE_END_INDEX = 2;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_POSITION_LEFT = 3;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_POSITION_TOP = 4;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_CONTENT_WIDTH = 5;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_CONTENT_HEIGHT = 6;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_CONTAINER_WIDTH = 7;
constexpr static MapBuffer::Key SLCONTAINER_STATE_SCROLL_CONTAINER_HEIGHT = 8;
constexpr static MapBuffer::Key SLCONTAINER_STATE_HORIZONTAL = 9;
constexpr static MapBuffer::Key SLCONTAINER_STATE_INITIAL_NUM_TO_RENDER = 10;
constexpr static MapBuffer::Key SLCONTAINER_STATE_FIRST_CHILD_UNIQUE_ID = 11;
constexpr static MapBuffer::Key SLCONTAINER_STATE_LAST_CHILD_UNIQUE_ID = 12;
#endif

class SLContainerState {
  public:
  SLContainerState(
    SLFenwickTree childrenMeasurementsTree,
    Point scrollPosition,
    Size scrollContainer,
    Size scrollContent,
    int visibleStartIndex,
    int visibleEndIndex,
    std::string firstChildUniqueId,
    std::string lastChildUniqueId,
    bool horizontal,
    int initialNumToRender);
  SLContainerState() = default;

  SLFenwickTree childrenMeasurementsTree;
  Point scrollPosition;
  Size scrollContainer;
  Size scrollContent;
  int visibleStartIndex;
  int visibleEndIndex;
  std::string firstChildUniqueId;
  std::string lastChildUniqueId;
  bool horizontal;
  int initialNumToRender;

  int calculateVisibleStartIndex(const float visibleStartOffset, const int offset = 5) const;
  int calculateVisibleEndIndex(const float visibleStartOffset, const int offset = 5) const;
  Point calculateScrollPositionOffset(const float visibleStartOffset) const;
  float calculateContentSize() const;
  float getScrollPosition(const Point& scrollPosition) const;

#ifdef ANDROID
  folly::dynamic childrenMeasurementsTreeToDynamic(SLFenwickTree childrenMeasurementsTree) const;
  MapBuffer childrenMeasurementsTreeToMapBuffer(SLFenwickTree childrenMeasurementsTree) const;
  SLFenwickTree childrenMeasurementsTreeFromDynamic(folly::dynamic childrenMeasurementsTree) const;
#endif

#ifdef ANDROID
  SLContainerState(SLContainerState const &previousState, folly::dynamic data) :
  childrenMeasurementsTree(
    childrenMeasurementsTreeFromDynamic(data["childrenMeasurementsTree"])
  ),
  scrollPosition({
    (Float)data["scrollPositionLeft"].getDouble(),
    (Float)data["scrollPositionTop"].getDouble()
  }),
  scrollContainer(previousState.scrollContainer),
  scrollContent(previousState.scrollContent),
  visibleStartIndex(
    calculateVisibleStartIndex(data["scrollPositionTop"].getDouble())
  ),
  visibleEndIndex(
    calculateVisibleEndIndex(data["scrollPositionTop"].getDouble())
  ),
  firstChildUniqueId(previousState.firstChildUniqueId),
  lastChildUniqueId(previousState.lastChildUniqueId),
  horizontal(previousState.horizontal),
  initialNumToRender(previousState.initialNumToRender) {};

  folly::dynamic getDynamic() const;
  MapBuffer getMapBuffer() const;
#endif
};

}
