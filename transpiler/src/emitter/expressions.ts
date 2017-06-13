import { ExpressionStatement, SyntaxKind, CallExpression, Identifier } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

export const emitExpressionStatement = ({ expression }: ExpressionStatement, context: Context): EmitResult =>
  emit(expression, context);

export const emitCallExpressionStatement = (node: CallExpression, context: Context): EmitResult => ({
  context,
  emitted_string: getCallExpressionEmit(node, context)
});

const getCallExpressionEmit = (node: CallExpression, context: Context): string => {
  const call_expression_name = emit(node.expression, context).emitted_string;
  const result = `${call_expression_name}(${node.arguments.map(a => emit(a, context).emitted_string).join(', ')});`;
  return wrapRunCall(call_expression_name, result, context);
}

const wrapRunCall = (call_expression_name: string, result: string, context: Context): string => {
  if (call_expression_name.slice(0, 5) !== 'riot_' || call_expression_name.slice(-4) !== '_run') return result;
  return context.run_wrapper.replace(':::', result);
}
