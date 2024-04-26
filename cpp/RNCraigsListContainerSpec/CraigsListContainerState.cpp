#include "CraigsListContainerState.h"

namespace facebook::react {

CraigsListContainerState::CraigsListContainerState(
  Point scrollPosition,
  Size scrollContainer,
  Size scrollContent,
  CraigsListFenwickTree scrollContentTree) :

    scrollPosition(scrollPosition),
    scrollContainer(scrollContainer),
    scrollContent(scrollContent),
    scrollContentTree(scrollContentTree) {}

/**
 * Measure layout and children metrics
 */
CraigsListContainerMetrics CraigsListContainerState::calculateLayoutMetrics(Point scrollPosition) const {
  int offset = 10;
  auto visibleStartPixels = std::max(0.0, scrollPosition.y);
  auto visibleEndPixels = std::min(scrollContent.height, scrollPosition.y + scrollContainer.height);

  int visibleStartIndex = scrollContentTree.lower_bound(visibleStartPixels);
  visibleStartIndex = std::max(0, visibleStartIndex - offset);

  int visibleEndIndex = scrollContentTree.lower_bound(visibleEndPixels);
  visibleEndIndex = std::min(scrollContentTree.size(), size_t(visibleEndIndex + offset));

  int blankTopStartIndex = 0;
  int blankTopEndIndex = std::max(0, visibleStartIndex - 1);

  auto blankTopStartPixels = 0.0;
  auto blankTopEndPixels = scrollContentTree.sum(blankTopStartIndex, blankTopEndIndex);

  int blankBottomStartIndex = std::min(size_t(visibleEndIndex + 1), scrollContentTree.size());
  int blankBottomEndIndex = scrollContentTree.size();

  auto blankBottomStartPixels = scrollContentTree.sum(blankBottomStartIndex, scrollContentTree.size());
  auto blankBottomEndPixels = scrollContentTree.sum(0, scrollContentTree.size());

  return CraigsListContainerMetrics{
    visibleStartIndex,
    visibleEndIndex,
    visibleStartPixels,
    visibleEndPixels,
    blankTopStartIndex,
    blankTopEndIndex,
    blankTopStartPixels,
    blankTopEndPixels,
    blankBottomStartIndex,
    blankBottomEndIndex,
    blankBottomStartPixels,
    blankBottomEndPixels,
  };
}

float CraigsListContainerState::calculateItemOffset(int index) const {
  return scrollContentTree.sum(0, index);
}

}
