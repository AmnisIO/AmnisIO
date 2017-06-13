import { Block } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

export const emitBlock = (node: Block, context: Context): EmitResult => {
  const emit_result =
    node.statements
      .reduce<EmitResult>(({ context, emitted_string }, node) => {
        const result = emit(node, context);
        result.emitted_string = emitted_string + '\n  ' + result.emitted_string;
        return result;
      }, { context, emitted_string: '' });
  return {
    ...emit_result,
    emitted_string: `{${emit_result.emitted_string}\n}`
  };
};
