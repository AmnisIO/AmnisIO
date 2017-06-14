import { ReturnStatement, VariableStatement, ExpressionStatement } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit, emitString } from './';

export const emitReturnStatement = ({ expression }: ReturnStatement, context: Context): EmitResult => {
  const emit_result = emit(expression, context);
  return {
    ...emit_result,
    emitted_string: `return ${emit_result.emitted_string};`
  };
};

export const emitVariableStatement = ({ declarationList: { declarations } }: VariableStatement, context: Context): EmitResult => ({
  context,
  emitted_string: declarations.map(node => emitString(node, context)).join(';\n') + ';'
});

export const emitExpressionStatement = ({ expression }: ExpressionStatement, context: Context): EmitResult => ({
  context,
  emitted_string: wrapRunCall(`${emitString(expression, context)};`, context)
});

const wrapRunCall = (result: string, { run, run_wrapper }: Context): string => 
  result.slice(0, run.length) !== run
    ? result
    : run_wrapper.replace(':::', result);
