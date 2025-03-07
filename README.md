# shadowlist [alpha release]

ShadowList is a new alternative to FlatList for React Native, created to address common performance issues and enhance the UX when dealing with large lists of data.
It invokes Yoga for precise layout measurements of Shadow Nodes and constructs a Fenwick Tree with layout metrics for efficient offset calculations. By virtualizing children and rendering only items within the visible area, ShadowList ensures optimal performance. It's built on Fabric and works with React Native version 0.75 and newer.

## Out of box comparison to FlatList
| Feature                          | ShadowList   | FlatList / FlashList   |
|----------------------------------|--------------|------------|
| 60 FPS Scrolling                 | ✅           | ❌         |
| No Estimated Size required       | ✅           | ❌         |
| No Content Flashing              | ✅           | ❌         |
| No Sidebar Indicator Jump        | ✅           | ❌         |
| Native Bidirectional List        | ✅           | ❌         |
| Instant initialScrollIndex       | ✅           | ❌         |
| Nested ShadowList (ScrollView)   | ✅           | ❌         |
| Natively Inverted List Support   | ✅           | ❌         |
| Smooth Scrolling                 | ✅           | ❌         |
| Dynamic Components               | ❌           | ✅         |

## Scroll Performance
| Number of Items  | ShadowList                 | FlatList             | FlashList            |
|------------------|----------------------------|----------------------|----------------------|
| 100 (text only)  | **~~156mb memory~~ - 60fps**   | ~~195mb~~ (38-43fps)     | ~~180mb (56fps)~~*   |
| 1000 (text only) | **~~187mb memory~~ - 60fps**   | ~~200mb~~ (33-38fps)     | ~~180mb (56fps)~~*   |

> **FlashList is unreliable and completely breaks when scrolling, resulting in unrealistic metrics.*  
> Given measurements show memory usage and FPS on fully loaded content, see demo [here](https://github.com/azimgd/shadowlist/issues/1) and implementation details [here](https://github.com/azimgd/shadowlist/blob/main/example/src/App.tsx).

## Important Note
Shadowlist doesn't support state updates or dynamic prop calculations inside the renderItem function. Any changes to child components should be made through the data prop. This also applies to animations. This restriction will be addressed in future updates.

## Installation
- CLI: Add the package to your project via `yarn add shadowlist` and run `pod install` in the `ios` directory.
- Expo: Add the package to your project via `npx expo install shadowlist` and run `npx expo prebuild` in the root directory.

## Usage

```js
import {Shadowlist} from 'shadowlist';

const stringify = (str: string) => `{{${str}}}`;

type ElementProps = {
  data: Array<any>;
};

const Element = (props: ElementProps) => {
  const handlePress = (event: GestureResponderEvent) => {
    const elementDataIndex = __NATIVE_getRegistryElementMapping(
      event.nativeEvent.target
    );
    props.data[elementDataIndex];
  };

  return (
    <Pressable style={styles.container} onPress={handlePress}>
      <Image source={{ uri: stringify('image') }} style={styles.image} />
      <Text style={styles.title}>{stringify('id')}</Text>
      <Text style={styles.content}>{stringify('text')}</Text>
      <Text style={styles.footer}>index: {stringify('position')}</Text>
    </Pressable>
  );
};

<Shadowlist
  contentContainerStyle={styles.container}
  ref={shadowListContainerRef}
  data={data}
  ListHeaderComponent={ListHeaderComponent}
  ListHeaderComponentStyle={styles.ListHeaderComponentStyle}
  ListFooterComponent={ListFooterComponent}
  ListHeaderComponentStyle={styles.ListFooterComponentStyle}
  ListEmptyComponent={ListEmptyComponent}
  ListEmptyComponentStyle={styles.ListFooterComponentStyle}
/>
```

## API
| Prop                       | Type                      | Required | Description                                     |
|----------------------------|---------------------------|----------|-------------------------------------------------|
| `data`                     | Array                     | Required | An array of data to be rendered in the list, where each item *must* include a required `id` field. |
| `contentContainerStyle`    | ViewStyle                 | Optional | These styles will be applied to the scroll view content container which wraps all of the child views. |
| `ListHeaderComponent`      | React component           | Optional | A custom component to render at the top of the list. |
| `ListHeaderComponentStyle` | ViewStyle                 | Optional | Styling for internal View for `ListHeaderComponent` |
| `ListFooterComponent`      | React component           | Optional | A custom component to render at the bottom of the list. |
| `ListFooterComponentStyle` | ViewStyle                 | Optional | Styling for internal View for `ListFooterComponent` |
| `ListEmptyComponent`       | React component           | Optional | A custom component to render when the list is empty. |
| `ListEmptyComponentStyle`  | ViewStyle                 | Optional | Styling for internal View for `ListEmptyComponent` |
| `initialScrollIndex`       | Number                    | Optional | The initial index of the item to scroll to when the list mounts. |
| `inverted`                 | Boolean                   | Optional | If true, the list will be rendered in an inverted order. |
| `horizontal`               | Boolean                   | Optional | If true, renders items next to each other horizontally instead of stacked vertically. |
| `onEndReached`             | Function                  | Optional | Called when the end of the content is within `onEndReachedThreshold`. |
| `onEndReachedThreshold`    | Double                    | Optional | The threshold (in content length units) at which `onEndReached` is triggered. |
| `onStartReached`           | Function                  | Optional | Called when the start of the content is within `onStartReachedThreshold`. |
| `onStartReachedThreshold`  | Double                    | Optional | The threshold (in content length units) at which `onStartReached` is triggered. |
| `numColumns`               | Number                    | Optional | Defines the number of columns in a grid layout. When enabled, the list will display items in a Masonry-style layout with variable item heights. |


## Methods
| Method          | Type                                | Description                                               |
|-----------------|-------------------------------------|-----------------------------------------------------------|
| `scrollToIndex` | Function                            | Scrolls the list to the specified index.                  |
| `scrollToOffset`| Function                            | Scrolls the list to the specified offset.                 |

## License

MIT
