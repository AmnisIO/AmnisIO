import { SyntaxKind, CallExpression, Identifier, ConditionalExpression, BinaryExpression, PropertyAccessExpression } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit, emitString } from './';

export const emitCallExpression = (node: CallExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(node.expression, context)}(${node.arguments.map(a => emitString(a, context)).join(', ')})`
});

export const emitConditionalExpression = ({ condition, questionToken, whenTrue, colonToken, whenFalse }: ConditionalExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(condition, context)} ${emitString(questionToken, context)} ${emitString(whenTrue, context)} ${emitString(colonToken, context)} ${emitString(whenFalse, context)}`
});

export const emitBinaryExpression = ({ left, right, operatorToken }: BinaryExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(left, context)} ${emitString(operatorToken, context)} ${emitString(right, context)}`
});

export const emitPropertyAccessExpression = ({ name, expression }: PropertyAccessExpression, context: Context): EmitResult => ({
  context,
  emitted_string: `${emitString(expression, context)}->${emitString(name, context)}`
});
