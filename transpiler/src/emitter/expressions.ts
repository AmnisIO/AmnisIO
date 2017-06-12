import { ExpressionStatement, SyntaxKind, CallExpression, Identifier } from 'typescript';

export const emitExpressionStatement = (node: ExpressionStatement): string => {
  switch(node.expression.kind) {
    case SyntaxKind.CallExpression: return emitCallExpressionStatement(<any>node.expression);
    default: throw new Error(`expression kind not supported ${node.expression.kind}`);
  }
}

const emitCallExpressionStatement = (node: CallExpression): string => {
  return 'call expression ' + (node.expression as Identifier).text + ' with arguments ' + node.arguments.map(a => (a as Identifier).text).join(', ');
}
