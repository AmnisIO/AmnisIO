import { BoardConfiguration } from './types';

export const config: BoardConfiguration = {
  platformio_identifier: 'uno',
  library_repositories: ['https://github.com/AmnisIO/gyrus.git', 'https://github.com/AmnisIO/rivulet.git'],
  library_file_globs: ['gyrus/src/*.{c,h}', 'rivulet/src/*.{c,h}'],
  exclude_library_file_globs: ['gyrus/src/Arduino.h']
};
