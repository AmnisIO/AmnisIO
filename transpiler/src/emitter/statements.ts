import { ReturnStatement, VariableStatement } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

export const emitReturnStatement = ({ expression }: ReturnStatement, context: Context): EmitResult => {
  const emit_result = emit(expression, context);
  return {
    ...emit_result,
    emitted_string: `return ${emit_result.emitted_string};`
  };
};

export const emitVariableStatement = ({ declarationList: { declarations } }: VariableStatement, context: Context): EmitResult => {
  const emit_result =
    declarations
      .reduce<EmitResult>(({ context, emitted_string }, node) => {
        const result = emit(node, context);
        result.emitted_string = emitted_string + ';\n  ' + result.emitted_string;
        return result;
      }, { context, emitted_string: '' });
  return {
    ...emit_result,
    emitted_string: `${emit_result.emitted_string};`
  };
};
