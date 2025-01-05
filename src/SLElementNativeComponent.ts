import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import type { ViewProps } from 'react-native';

declare global {
  var __NATIVE_registerElementNode: (node: any) => void;
  var __NATIVE_unregisterElementNode: (node: any) => void;
}

export interface SLElementNativeProps extends ViewProps {
  uniqueId: string;
}

export default codegenNativeComponent<SLElementNativeProps>('SLElement');
