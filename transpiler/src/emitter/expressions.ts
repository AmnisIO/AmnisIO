import { ExpressionStatement, SyntaxKind, CallExpression, Identifier, ConditionalExpression, BinaryExpression } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit, emitString } from './';

export const emitExpressionStatement = ({ expression }: ExpressionStatement, context: Context): EmitResult =>
  emit(expression, context);

export const emitCallExpression = (node: CallExpression, context: Context): EmitResult => ({
  context,
  emitted_string: getCallExpressionEmit(node, context)
});

export const emitConditionalExpression = ({ condition, questionToken, whenTrue, colonToken, whenFalse }: ConditionalExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(condition, context)} ${emitString(questionToken, context)} ${emitString(whenTrue, context)} ${emitString(colonToken, context)} ${emitString(whenFalse, context)}`
});

export const emitBinaryExpression = ({ left, right, operatorToken }: BinaryExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(left, context)} ${emitString(operatorToken, context)} ${emitString(right, context)}`
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
