import { ExpressionStatement, SyntaxKind, CallExpression, Identifier } from 'typescript';
import { Context } from '../contexts';
import { EmitResult } from './';

export const emitExpressionStatement = (node: ExpressionStatement, context: Context): EmitResult => {
  switch (node.expression.kind) {
    case SyntaxKind.CallExpression: return emitCallExpressionStatement(<any>node.expression, context);
    default: throw new Error(`expression kind not supported ${node.expression.kind}`);
  }
}

const emitCallExpressionStatement = (node: CallExpression, context: Context): EmitResult => ({
  context,
  emitted_string: 'call expression ' + (node.expression as Identifier).text + ' with arguments ' + node.arguments.map(a => (a as Identifier).text).join(', ')
});
