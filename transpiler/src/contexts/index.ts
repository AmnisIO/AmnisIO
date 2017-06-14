import { context as unoContext } from './arduino-uno';

export interface Context {
  [x: string]: string;
  run_wrapper: string;
  run: string;
}

interface IndexedContexts {
  [x: string]: Context;
}

const contexts = {
  'arduino-uno': unoContext
};

export const getContext = (key: string) => contexts[key];
