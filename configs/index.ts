import { BoardConfiguration} from './types';
import { config as unoConfig } from './arduino-uno';

export interface IndexedConfigs {
  [x: string]: BoardConfiguration;
}

export const configs: IndexedConfigs  = {
  'uno': unoConfig
};
