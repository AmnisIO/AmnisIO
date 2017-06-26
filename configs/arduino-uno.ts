import { BoardConfiguration } from './types';

export const config: BoardConfiguration = {
  board: 'uno',
  libraries: [
    {
      repository: 'https://github.com/AmnisIO/gyrus',
      paths: ['arduino_uno/src']
    },
    {
      repository: 'https://github.com/AmnisIO/rivulet',
      paths: ['src']
    }
  ]
};
