import { EmitResult, emit } from './';
import { Context } from '../contexts';
import { SourceFile } from 'typescript';

export const emitSourceFile = (node: SourceFile, context): EmitResult =>
  node.statements
    .reduce((result, node) => {
      const emit_result = emit(node, context);
      emit_result.emitted_string = result.emitted_string + '\n' + emit_result.emitted_string;
      return emit_result;
    }, { context, emitted_string: '' });
