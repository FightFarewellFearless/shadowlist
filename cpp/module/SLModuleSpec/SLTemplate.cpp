#include "SLTemplate.h"
#include "SLRuntimeManager.h"
#include <react/renderer/components/text/RawTextShadowNode.h>
#include <react/renderer/components/image/ImageShadowNode.h>

namespace facebook::react {

int nextFamilyTag = -2;

auto adjustFamilyTag = [](int tag) {
  const int MIN_TAG_VALUE = -2e9;
  const int CLAMPED_TAG = -2;
  return tag < MIN_TAG_VALUE ? CLAMPED_TAG : tag - 2;
};

static void updateRawTextProps(const SLContainerProps::SLContainerDataItem &elementData, const std::shared_ptr<ShadowNode> &nextShadowNode, const ShadowNode::Shared &shadowNode) {
  if (shadowNode->getComponentName() != std::string("RawText")) {
    return;
  }

  RawTextShadowNode::ConcreteProps* updatedProps = const_cast<RawTextShadowNode::ConcreteProps*>(
    static_cast<const RawTextShadowNode::ConcreteProps*>(nextShadowNode->getProps().get()));
  auto path = SLKeyExtractor::extractKey(updatedProps->text);
  updatedProps->text = SLContainerProps::getElementValueByPath(elementData, path);
}

static void updateImageProps(const SLContainerProps::SLContainerDataItem &elementData, const std::shared_ptr<ShadowNode> &nextShadowNode, const ShadowNode::Shared &shadowNode) {
  if (shadowNode->getComponentName() != std::string("Image")) {
    return;
  }

  ImageShadowNode::ConcreteProps* updatedProps = const_cast<ImageShadowNode::ConcreteProps*>(
    static_cast<const ImageShadowNode::ConcreteProps*>(nextShadowNode->getProps().get()));
  auto path = SLKeyExtractor::extractKey(updatedProps->sources[0].uri);
  updatedProps->sources[0].uri = SLContainerProps::getElementValueByPath(elementData, path);
}

ShadowNode::Unshared SLTemplate::cloneShadowNodeTree(const SLContainerProps::SLContainerDataItem &elementData, const ShadowNode::Shared& shadowNode)
{
  auto const &componentDescriptor = shadowNode->getComponentDescriptor();
  PropsParserContext propsParserContext{shadowNode->getSurfaceId(), *componentDescriptor.getContextContainer().get()};

  nextFamilyTag = adjustFamilyTag(nextFamilyTag);

  InstanceHandle::Shared instanceHandle = std::make_shared<const InstanceHandle>(
    *SLRuntimeManager::getInstance().getRuntime(),
    shadowNode->getInstanceHandle(*SLRuntimeManager::getInstance().getRuntime()),
    shadowNode->getTag());
  auto const fragment = ShadowNodeFamilyFragment{nextFamilyTag, shadowNode->getSurfaceId(), instanceHandle};
  auto const family = componentDescriptor.createFamily(fragment);
  auto const props = componentDescriptor.cloneProps(propsParserContext, shadowNode->getProps(), {});
  auto const state = componentDescriptor.createInitialState(props, family);
  auto const nextShadowNode = componentDescriptor.createShadowNode(
    ShadowNodeFragment{props, ShadowNodeFragment::childrenPlaceholder(), state}, family);

  updateRawTextProps(elementData, nextShadowNode, shadowNode);
  updateImageProps(elementData, nextShadowNode, shadowNode);

  for (const auto &childShadowNode : shadowNode->getChildren()) {
    auto const clonedChildShadowNode = cloneShadowNodeTree(elementData, childShadowNode);
    componentDescriptor.appendChild(nextShadowNode, clonedChildShadowNode);
  }

  return nextShadowNode;
}

}
