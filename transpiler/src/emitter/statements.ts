import { ReturnStatement } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

export const emitReturnStatement = ({ expression }: ReturnStatement, context: Context): EmitResult => {
  const emit_result = emit(expression, context);
  return {
    ...emit_result,
    emitted_string: `return ${emit_result.emitted_string};`
  };
};
